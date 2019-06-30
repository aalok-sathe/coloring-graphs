#!/usr/bin/env python3

import argparse
import subprocess
import webbrowser
import sys
from os.path import expanduser
from pathlib import Path
from flask import Flask, url_for, request, render_template, json
from collections import defaultdict
import webbrowser

import libcolgraph as lcg


app = Flask(__name__)

global args
parser = argparse.ArgumentParser()
parser.add_argument('-i', '--input-file', type=str,
                    help='read in BaseGraph from adjacency matrix file',
                    default=expanduser('~')
                            + '/code/coloring-graphs/in/hexmodsegfault.in')
parser.add_argument('-k', '--colors', type=int, default=3,
                    help='number of colors to use to create ColoringGraph')
parser.add_argument('-n', '--new', default=False, action='store_true',
                    help='open a blank canvas?')
parser.add_argument('-v', '--verbosity', action='count', default=0,
                    help='set output verbosity')
parser.add_argument('-p', '--port', default='5000', type=str,
                    help='port to launch GUI on')
args = parser.parse_args()

global data
data = dict()


# def preprequest():
#     '''
#     '''


@app.route('/', methods=['POST', 'GET'])
def index():
    '''
    '''
    if request.method == 'GET':
        global data
        print('handling GET on index!')
        data.update(dict(colors=str(args.colors)))
        return render_template('defaultview.html', **data)

    elif request.method == 'POST':
        requestdata = request.get_json()
        # print(requestdata)
        print('handling POST on index!')

        graphdata = requestdata[0]
        args.colors = int(requestdata[1])
        data.update(dict(colors=args.colors))

        bg = lcg.viz.from_visjs(graphdata)
        cg = bg.build_coloring_graph(args.colors)
        mcg = cg.tarjans()
        pcg = mcg.rebuild_partial_graph()

        data.update(lcg.viz.to_visjs(bg))
        data.update(lcg.viz.to_visjs(cg))
        data.update(lcg.viz.to_visjs(mcg, force_type='mcg'))
        data.update(lcg.viz.to_visjs(pcg, force_type='pcg'))

        statsdict = dict(
                size=len(cg),
                is_connected=cg.is_connected(),
                is_biconnected=cg.is_biconnected(),
            )

        retdict = {
            'cgcontainer': render_template('graphcontainer.html',
                                           container_type='cg', **data),
            'mcgcontainer': render_template('graphcontainer.html',
                                            container_type='mcg', **data),
            'pcgcontainer': render_template('graphcontainer.html',
                                            container_type='pcg', **data),
            'cgstats': ' '.join(['{}: {},'.format(k, v)
                                 for k, v in statsdict.items()]),
            'size': statsdict['size']
                    }

        response = app.response_class(status=200, response=json.dumps(retdict),
                                      mimetype='application/json')

        return response



def flaskgui(url='http://localhost', port='5000'):
    '''
    '''
    app.config['ENV'] = 'development'
    app.config['DEBUG'] = True
    app.config['TESTING'] = True

    bg = lcg.BaseGraph()
    cg = bg.build_coloring_graph(args.colors)
    mcg = cg.tarjans()
    pcg = mcg.rebuild_partial_graph()

    if not args.new:
        bg.load_txt(args.input_file)
        #mbg = bg.tarjans()


    global data
    data.update(lcg.viz.to_visjs(bg))
    # data.update(lcg.viz.to_visjs(cg))
    # data.update(lcg.viz.to_visjs(mcg, force_type='mcg'))
    # data.update(lcg.viz.to_visjs(pcg, force_type='pcg'))

    app.run(port=port)


def main():
    '''
    '''
    url = 'http://localhost'
    port = args.port
    # webbrowser.open_new(url + ':{port}'.format(port=port))
    flaskgui(url, port)


if __name__ == '__main__':
    main()
