#!/usr/bin/env python3

import argparse
import subprocess
import webbrowser
import sys
from pathlib import Path
from flask import Flask, url_for, request, render_template
from collections import defaultdict
import webbrowser

import libcolgraph as lcg


app = Flask(__name__)
global args
args = defaultdict(None)


@app.route('/')
def index():
    '''
    '''
    # path = '/home/aalok/code/coloring-graphs/in/bipartite_test_graph0.in'
    bg = lcg.BaseGraph()
    if not args.new:
        bg.load_txt(args.input_file)
        #mbg = bg.tarjans()
    
    cg = bg.build_coloring_graph(args.colors)  
    mcg = cg.tarjans()
    
    data = dict()
    data.update(lcg.viz.to_visjs(bg))
    data.update(lcg.viz.to_visjs(cg))
    data.update(lcg.viz.to_visjs(mcg))
    
    return render_template('defaultview.html', **data)


def djangogui():
    '''
    launcher for the web webgui
    '''
    
    raise DeprecationWarning
    
    command = ['python3', str(Path(__file__).parent/'manage.py'), 'runserver', '3142']
    proc = subprocess.Popen(command, stdout=subprocess.PIPE, 
                            stderr=subprocess.PIPE)
    stdout, stderr = proc.communicate()
    
    if args.verbosity:
        print(stdout, file=sys.stdout)
        print(stderr, file=sys.stderr)
    
    webbrowser.open_new('http://localhost:3142')
    
   
def flaskgui(url='http://localhost', port='5000'):
    '''
    '''
    app.config['ENV'] = 'development'
    app.config['DEBUG'] = True
    app.config['TESTING'] = True

    app.run(port=port)


def main():
    '''
    '''
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input-file', type=str,
                        help='read in BaseGraph from adjacency matrix file',
                        default='/home/aalok/code/coloring-graphs/in/hexmod.in')
    parser.add_argument('-k', '--colors', type=int, default=3,
                        help='number of colors to use to create ColoringGraph')
    parser.add_argument('-n', '--new', default=False, action='store_true',
                        help='open a blank canvas?')
    parser.add_argument('-v', '--verbosity', action='count', default=0,
                        help='set output verbosity')
    global args
    args = parser.parse_args()
 
    url = 'http://localhost'
    port = '5000'
    # webbrowser.open_new(url + ':{port}'.format(port=port))
    flaskgui(url, port)


if __name__ == '__main__':
    main()
