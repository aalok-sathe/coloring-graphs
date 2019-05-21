#!/usr/bin/env python3

# import graph_tool as gt
from pathlib import Path
from Vertex import Vertex
import typing
from tqdm import tqdm

class Graph:#(gt.Graph):
    '''
    OG graph class
    '''
    n = None
    vertices = None

    def __init__(self, *args, **kwargs):
        # super().__init__(*args, **kwargs, directed=False)
        self.vertices = []

    def __len__(self) -> int:
        '''
        override len method to get size
        '''
        if self.n:
            return self.n
        return 0

    def load_txt(self, path: typing.Union[str, Path]) -> None:
        '''
        loads a text file containing a description of a graph and constructs
        internal representation of it.
        the text file must have a single line containing |V| followed by
        |V| lines that together make up an adjacency matrix
        '''
        if not isinstance(path, Path):
            path = Path(path)
        with path.open(mode='r') as f:
            self.n = int(f.readline())
            self.vertices = [Vertex() for _ in range(self.n)]
            for i, line in enumerate(f):
                if i >= self.n: break
                adjacent = [ix for ix, v in enumerate(line.split()) if int(v)]
                self.vertices[i].add_neighbors(*[self.vertices[j]
                                               for j in adjacent])


    def get_vertic


    def get_some_vertex(self) -> Vertex:
        '''
        gets some arbitrary vertex of the graph
        '''
        for v in self.get_vertices():
            return v


    def reset_attrs(self, *attrs: list) -> None:
        '''
        sets the supplied attributes to None for each vertex
        '''
        for v in self.vertices():
            for attr in attrs:
                v[attr] = None


class BaseGraph(Graph):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)


    def get_coloring_graph(self) -> typing.NewType('ColoringGraph', Graph):
        '''
        generates and returns a ColoringGraph object for the current
        BaseGraph object
        '''
        pass


class ColoringGraph(Graph):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)



def Tarjans(g: Graph):
    '''
    '''
    root = g.get_some_vertex()


    #assuming for now that the graph is weakly connected
