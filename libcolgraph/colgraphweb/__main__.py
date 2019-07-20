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
import random
import time
import PySimpleGUI as sg

import libcolgraph as lcg


app = Flask(__name__)

global args
parser = argparse.ArgumentParser()
parser.add_argument('-i', '--input-file', type=str,
                    help='read in BaseGraph from adjacency matrix file',
                    default=None)
                    # default=str(Path(__file__).parent/'../in/hexmod.in'))
parser.add_argument('-n', '--new', default=True, action='store_true',
                    help='open a blank canvas?')
parser.add_argument('-s', '--select_file', default=False, action='store_true',
                    help='open file choosing gui dialogue?')
parser.add_argument('-k', '--colors', type=int, default=3,
                    help='number of colors to use to create ColoringGraph')
parser.add_argument('-v', '--verbosity', action='count', default=0,
                    help='set output verbosity')
parser.add_argument('-p', '--port', default='5000', type=str,
                    help='port to launch GUI on')
parser.add_argument('-w', '--webbrowser', default=False, action='store_true',
                    help='open app in default web browser window?')
parser.add_argument('-r', '--render_on_launch', default=False,
                    action='store_true', help='render to-generate componenets '
                                              'on initial launch?')
parser.add_argument('-d', '--debug', default=False, action='store_true',
                    help='launch Flask app in debug mode?')
parser.add_argument('-t', '--threaded', default=False, action='store_true',
                    help='allow multiple threads?')

args = parser.parse_args()

global data
data = dict()


colors = {
            'red': '#ef5350',
            'blue': '#039be5',
            'green': '#4caf50',
            'yellow': '#ffee58',
            'pink': '#f48fb1',
            'purple': '#673ab7',
            'brown': '#795548',
            'white': '#f5f5f5',
            'cyan': '#18ffff',
            'orange': '#ff9100',
            'grey': '#bdbdbd',
            'lightgreen': '#76ff03',
         }
colororder = ['yellow', 'green', 'purple', 'white', 'pink', 'cyan', 'brown']

colorarray = {}
colorarray.update(colors)
colorarray.pop('red')
colorarray.pop('blue')
colorarray = [*colorarray.keys()]
random.shuffle(colorarray)
colorarray.sort(key=lambda x: colororder.index(x) if colororder.count(x) else
                              float('inf'))


@app.route('/favicon.ico', methods=['GET'])
def favicon():
    '''
    returns a favicon on a GET request
    '''
    return flask.send_from_directory(os.path.join(app.root_path, 'static'),
                                     'favicon.ico')


@app.route('/', methods=['GET'])
def index():
    '''
    '''
    # if request.method != 'GET':
    #     raise RuntimeError

    global data
    print('handling GET on index!')
    data.update(dict(colors=str(args.colors)))

    app.cghtml = None
    app.statsdict = defaultdict(None)

    return render_template('defaultview.html', **data)


def cvcolorfngen(cut_verts, mother_verts=[]):
    '''
    '''
    def get_color(v):
        if v.get_name() in mother_verts:
            return 'red'
        if v.get_name() in cut_verts:
            return 'yellow'
        return None

    return get_color


def update_bg_data(bg):
    '''
    '''
    global data
    data.update(lcg.viz.to_visjs(bg, colordict=colors, colorfn=lambda v: None))


def update_cg_data(cg):
    '''
    '''
    global data
    data.update(lcg.viz.to_visjs(cg, colordict=colors,
                                 colorfn=cvcolorfngen(app.cut_verts,
                                                      app.mother_verts)))


def update_mcg_data(mcg):
    '''
    '''
    global data
    # data.update(lcg.viz.to_visjs(mcg))
    data.update(lcg.viz.to_visjs(mcg, colordict=colors,
                                 colorfn=cvcolorfngen(app.cut_verts,
                                                [mcg.identify_mothership()]
                                                      )))


def update_pcg_data(pcg):
    '''
    '''
    global data
    data.update(lcg.viz.to_visjs(pcg, force_type='pcg', colordict=colors,
                                 colorfn=cvcolorfngen(app.cut_verts,
                                                      app.mother_verts)))


@app.route('/generate', methods=['POST'])
def generate():
    '''
    '''
    requestdata = request.get_json()
    # print(requestdata)
    print('handling POST on generate!')

    global data

    graphdata = requestdata[0]
    args.colors = int(requestdata[1])
    data.update(dict(colors=args.colors))

    app.bg = bg = lcg.viz.from_visjs(graphdata)
    update_bg_data(bg)
    random.shuffle(colorarray[len(colororder):])

    start = time.time()
    app.cg = cg = bg.build_coloring_graph(args.colors)
    end = time.time()
    print('INFO: generated a coloring graph {} from {}'.format(cg, bg),
          'in {} seconds'.format(end - start))

    start = time.time()
    app.mcg = mcg = cg.tarjans()
    end = time.time()
    print('INFO: ran tarjans on graph {}'.format(cg),
          'in {} seconds'.format(end - start))

    app.cut_verts = cut_verts = [*mcg.get_cut_vertices()]
    update_mcg_data(mcg)

    start = time.time()
    app.pcg = pcg = mcg.rebuild_partial_graph()
    end = time.time()
    print('INFO: rebuilt a partial coloring graph {} from {}'.format(pcg, mcg),
          'in {} seconds'.format(end - start))

    app.mother_verts = mother_verts = [*mcg.get_mothership_cut_vertices()]
    update_pcg_data(pcg)

    app.statsdict = statsdict = dict(
            cgsize=len(cg),
            is_connected=cg.is_connected(),
            is_biconnected=cg.is_biconnected(),
        )

    retdict = {
        'bgcontainer': render_template('graphcontainer.html',
                                        container_type='bg', **data),
        'mcgcontainer': render_template('graphcontainer.html',
                                        container_type='mcg', **data),
        'pcgcontainer': render_template('graphcontainer.html',
                                        container_type='pcg', **data),
        'cgsize': app.statsdict['cgsize'],
                }


    if len(cg) <= 512:
        update_cg_data(cg)
        app.cghtml = render_template('graphcontainer.html',
                                 container_type='cg', **data)
        retdict.update({'cgcontainer': app.cghtml})

    response = app.response_class(status=200, response=json.dumps(retdict),
                                  mimetype='application/json')

    return response


@app.route('/cgdata', methods=['POST'])
def get_cg_data():
    '''
    '''
    requestdata = request.get_json()
    # print(requestdata)
    print('handling POST on get_cg_data!')

    update_cg_data(app.cg)
    app.cghtml = render_template('graphcontainer.html',
                                 container_type='cg', **data)
    retdict = {'cgcontainer': app.cghtml}

    response = app.response_class(status=200, response=json.dumps(retdict),
                                  mimetype='application/json')

    return response


@app.route('/cgstats', methods=['POST'])
def get_stats():
    '''
    '''
    requestdata = request.get_json()
    # print(requestdata)
    print('handling POST on get_stats!')

    retdict = {
        'stats': ' '.join(['{}: {},'.format(k, v)
                             for k, v in app.statsdict.items()]),
              }

    response = app.response_class(status=200, response=json.dumps(retdict),
                                  mimetype='application/json')

    return response



@app.route('/colorbg_from_mcg', methods=['POST'])
def colorbg_from_mcg():
    '''
    returns a coloring specification to pass to the graph drawing utility
    using a vertex of the meta coloring graph. the important thing to note is
    that a MetaVertex can represent multiple colorings, so only the fixed
    coloring positions will be so colored in the basegraph
    '''
    requestdata = request.get_json()
    whatclicked = requestdata[1]

    if whatclicked == 'node':
        selected_meta_vertex = requestdata[0][0]
        selected_meta_vertex = app.mcg.get_vertex(selected_meta_vertex)

        vertices = [*selected_meta_vertex.get_vertices()]
        coloring = app.cg.get_possible_colors(vertices)
        app.statsdict.update(dict(MetaVertex_size=len(selected_meta_vertex)))

        return colorbg(coloring,
                       stats=' '.join(['{}: {},'.format(k, v)
                                       for k, v in app.statsdict.items()]))

    elif whatclicked == 'edge':
        selected_edge = requestdata[0][0]
        (a, b) = selected_edge.split()
        avertices = [*app.mcg.get_vertex(int(a)).get_vertices()]
        bvertices = [*app.mcg.get_vertex(int(b)).get_vertices()]

        coloring = app.cg.get_possible_colors(avertices+bvertices)
        return colorbg(coloring)


@app.route('/colorbg_from_cg', methods=['POST'])
def colorbg_from_cg():
    '''
    returns a colorfn to pass to the graph drawing utility. a single coloring
    vertex fully specifies the coloring of the basegraph, and so the basegraph
    will be fully colored based on the output of this method
    '''
    # print(requestdata)
    requestdata = request.get_json()
    whatclicked = requestdata[1]

    if whatclicked == 'node':
        selected_vertex = requestdata[0][0]
        coloring = app.cg.get_possible_colors([selected_vertex])

        return colorbg(coloring)

    elif whatclicked == 'edge':
        selected_edge = requestdata[0][0]
        (a, b) = selected_edge.split()

        coloring = app.cg.get_possible_colors([int(a), int(b)])
        return colorbg(coloring)

    else:
        raise RuntimeWarning


@app.route('/colorbg', methods=['POST'])
def colorbg(coloring_list=None, **kwargs):
    '''
    given a list of colors (or indetermined colors) for the basegraph, with
    each position in the list corresponding to a vertex, returns a colored
    view of the basegraphbased on that coloring. this function defines the
    colorfn based on supplied coloring_list
    '''
    if not coloring_list:
        requestdata = request.get_json()
        coloring_list = requestdata[0]

    def color_from_coloring_list(v):
        name = v.get_name()
        if len(coloring_list[name]) == 1:
            return colorarray[list(coloring_list[name])[0]]
        try:
            return [colorarray[c] for c in list(coloring_list[name])]
        except IndexError as e:
            print('ERROR: too many colors')
            return None

    data.update(lcg.viz.to_visjs(app.bg, colordict=colors,
                                 colorfn=color_from_coloring_list))

    retdict = {
        'bgcontainer': render_template('graphcontainer.html',
                                        container_type='bg', **data),
              }
    retdict.update(kwargs)

    response = app.response_class(status=200, response=json.dumps(retdict),
                                  mimetype='application/json')

    return response


def to_matrix_str(g):
    '''
    '''
    lookup = dict()
    for i, v in enumerate(g.get_vertices()):
        lookup[v.get_name()] = i

    ret = '%d\n' % len(g)

    mat = [['0' for _ in range(len(g))] for _ in range(len(g))]
    for v in g.get_vertices():
        for n in v.get_neighbors():
            mat[lookup[v.get_name()]][lookup[n]] = '1'
            mat[lookup[n]][lookup[v.get_name()]] = '1'

    for line in mat:
        ret += ' '.join(line) + '\n'

    return ret


@app.route('/save', methods=['POST'])
def save_graph():
    '''
    '''
    requestdata = request.get_json()
    # print(requestdata)
    print('handling POST on save!')

    global data
    # graphdata = requestdata[0]
    # app.bg = bg = lcg.viz.from_visjs(graphdata)

    w = sg.Window('Save graph').Layout([[sg.Text('Filename')], [sg.Input(), sg.FileSaveAs()], [sg.OK(), sg.Cancel()] ])
    event, values = w.Read()
    w.Close()

    if event == 'OK':
        dest = Path(values[0])

        bgmat = to_matrix_str(app.bg)
        mcgmat = to_matrix_str(app.mcg)
        # pcgmat = to_matrix_str(app.pcg)

        with dest.open('w') as f:
            f.write(bgmat)
            f.write(mcgmat)
            # f.write(pcgmat)

        response = app.response_class(status=200, mimetype='application/json',
                                      response=json.dumps({'status': 'OK'}))

        return response
    return None


@app.route('/load', methods=['POST'])
def load_graph_from_file():
    '''
    loads an input graph from a file
    '''
    w = sg.Window('Get filename').Layout([[sg.Text('Filename')], [sg.Input(), sg.FileBrowse()], [sg.OK(), sg.Cancel()] ])

    event, values = w.Read()
    w.Close()
    if event == 'OK':
        resp = values[0]
        if resp and Path(resp).exists():
            args.input_file = resp
            bg = lcg.BaseGraph()
            bg.load_txt(args.input_file)
            app.bg = bg
            update_bg_data(app.bg)
        else:
            raise ValueError

    retdict = {
        'bgcontainer': render_template('graphcontainer.html',
                                        container_type='bg', **data),
              }
    response = app.response_class(status=200, response=json.dumps(retdict),
                                  mimetype='application/json')
    return response


@app.route('/generate_random', methods=['POST'])
def generate_random():
    '''
    generates a randomgraph
    '''
    w = sg.Window('Enter Erdos-Reyni values:').Layout([
            [sg.Text('number of vertices (V) '
                     'and probability of spawning edges (p)')],
            [sg.Text('V'), sg.Input()],
            [sg.Text('p'), sg.Input()],
            [sg.OK(), sg.Cancel()]
        ])

    event, values = w.Read()
    w.Close()
    if event == 'OK':
        print(values)
        v, p  = int(values[0]), float(values[1])
        if (v, p):
            bg = lcg.BaseGraph()
            bg.generate_random(v, p)
            app.bg = bg
            update_bg_data(app.bg)
        else:
            raise ValueError

    retdict = {
        'bgcontainer': render_template('graphcontainer.html',
                                        container_type='bg', **data),
              }
    response = app.response_class(status=200, response=json.dumps(retdict),
                                  mimetype='application/json')
    return response


def runflaskgui(url='http://localhost', port='5000'):
    '''
    '''
    app.config['ENV'] = 'development'
    app.config['DEBUG'] = args.debug
    app.config['TESTING'] = True

    bg = lcg.BaseGraph()
    if args.input_file:
        bg.load_txt(args.input_file)
    app.bg = bg

    update_bg_data(bg)

    if args.render_on_launch:
        app.cg = cg = bg.build_coloring_graph(args.colors)
        app.mcg = mcg = cg.tarjans()
        app.cut_verts = cut_verts = [*mcg.get_cut_vertices()]
        app.pcg = pcg = mcg.rebuild_partial_graph()
        app.mother_verts = mother_verts = [*mcg.get_mothership_cut_vertices()]

        update_mcg_data(mcg)
        update_cg_data(cg)
        update_pcg_data(pcg)

        app.statsdict = statsdict = dict(
            cgsize=len(cg),
            is_connected=cg.is_connected(),
            is_biconnected=cg.is_biconnected(),
        )
        data.update({'stats': ' '.join(['{}: {},'.format(k, v)
                                for k, v in app.statsdict.items()])})

    app.run(port=port, threaded=args.threaded)


def main():
    '''
    '''
    url = 'http://localhost'
    port = args.port
    if args.webbrowser:
        webbrowser.open_new(url + ':{port}'.format(port=port))

    if args.select_file:
        w = sg.Window('Get filename').Layout([[sg.Text('Filename')], [sg.Input(), sg.FileBrowse()], [sg.OK(), sg.Cancel()] ])
        event, values = w.Read()
        w.Close()
        if event == 'OK':
            resp = values[0]
            if resp and Path(resp).exists():
                args.input_file = resp
            else:
                print('Unable to load file. Opening blank canvas')

    runflaskgui(url, port)


if __name__ == '__main__':
    main()
