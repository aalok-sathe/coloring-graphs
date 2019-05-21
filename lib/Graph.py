#!/usr/bin/env python3

import graph_tool as gt
from pathlib import Path
from Vertex import Vertex

class Graph(gt.Graph):
    '''
    OG graph class
    '''
    n = None
    vertices = None

    def __init__(self, *args):
        super().__init__(*args, directed=False)

    
    def load_txt(self, path):
        if not isinstance(path, Path):
            path = Path(path)
        with path.open(mode='r') as f:
            self.n = int(f.readline())
                 

    def get_some_vertex(self):
        for v in vertices():
            return v
    

class BaseGraph(Graph):



class ColoringGraph(Graph):

  


def Tarjans(g: Graph):
    '''
    '''
    root = g.get_some_vertex()
    
    
    #assuming for now that the graph is weakly connected
