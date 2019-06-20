#! /bin/env/ python3

import pyvis
import json
import math


def to_pyvis_network(g, *args, **kwargs):
    '''
    method to return a pyvis Network object from Graph<> `g`
    '''
    net = pyvis.network.Network()
    for v in g.get_vertices():
        net.add_node(v.get_name(), size=32*math.pow(len(v), 1/3),
                     group=str(len(v)))
                     
    for v in g.get_vertices():
        try:
            for nname in v.get_neighbors():
                net.add_edge(v.get_name(), nname)
        except IndexError as e:
            continue
            
    return net


def to_visjs(g, *args, **kwargs):
    '''
    takes in a graph which is a subclass of Graph<> (see GraphTemplates.h)
    and produces a json object that specifies how the graph should be plotted
    in a way that VisJS can use
    '''
    net = to_pyvis_network(g)
    nodes, edges, height, width, options = net.get_network_data()
    
    prefix = ''
    typestr = str(type(g))
    # print(typestr)
    if 'Base' in typestr: prefix = 'bg'
    elif 'Coloring' in typestr: prefix = 'cg'
    else: prefix = 'mcg'
    
    data = {prefix+'nodes': json.dumps(nodes), 
            prefix+'edges': json.dumps(edges)}
            
    return data
