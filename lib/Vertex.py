#!/usr/bin/env python3

#import graph_tool as gt
from pathlib import Path
from collections import defaultdict
import typing
from utils import mathtools

# vertex attributes
ID = 'id'
COLORS = 'colors'
NAME = 'name'
GRAPH = 'graph'

class Vertex:#(gt.Vertex):
    attrs = None
    neighbors = None

    def __init__(self, i=None):
        # super().__init__(*args)
        self.attrs = defaultdict(None)
        self.neighbors = set()

        self[ID] = i


    def __getitem__(self, key):
        '''
        overridden method to support getting attributes
        e.g. c = vertex[COLOR]
        if attribute doesn't exist, returns None
        '''
        return self.attrs[key]


    def __setitem__(self, key, value):
        '''
        overridden method to support setting attributes
        e.g. vertex[COLOR] = 2
        '''
        self.attrs[key] = value


    def __str__(self) -> str:
        '''
        '''
        returnable = '{}\t'.format(repr(self))
        returnable += 'neighbors: ' + str(self.get_neighbors())

        for k, v in self.attrs.items():
            returnable += '{}: {} '.format(k, v)

        returnable += 'number of neighbors: '
        returnable += '%d ' % len([*self.get_neighbors()])

        return returnable



    def add_neighbors(self, *vertices: typing.Container[__name__]):
        '''
        adds vertices to self's neighboring vertices
        '''
        for v in vertices:
            self.neighbors.add(v)


    def get_neighbors(self) -> typing.Set[__name__]:
        '''
        returns neighbors of self
        '''
        return self.neighbors



class ColoringVertex(Vertex):

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)


    def __str__(self) -> str:
        '''
        '''
        returnable = super().__str__()
        returnable += 'coloring: %s ' % mathtools.convert_base(self[NAME],
                                                              self[COLORS])
        return returnable


    def add_neighbors(self, *vertices: typing.Container[__name__]):
        '''
        adds vertices to self's neighboring vertices
        '''
        raise NotImplementedError('no support to add neighbors to a '
                                  'ColoringVertex. please read the docs')



    def get_color(self, coloring: int=0) -> int:
        '''
        returns the color of the vertex in the given coloring bitstring
        '''
        return (coloring // self[COLORS] ** self[ID]) % self[COLORS]


    def get_neighbors(self) -> typing.Set[__name__]:
        '''
        returns neighbors of self
        '''
        return self.get_possible_neighbors(n=len(self.graph))


    def get_possible_neighbors(self, n: int=None):
        '''
        creates a generator over all possible (potential) neighbors
        of a vertex, given coloring size k
        '''
        coloring = self[NAME]
        # manipulate each position for a potential neighbor
        for position in range(n):
            curcol = (coloring // self[COLORS] ** position) % self[COLORS]
            # try each alternate coloring other than current
            for c in range(self[COLORS]):
                if c == curcol: continue
                newcoloring = coloring // self[COLORS] ** position
                newcoloring -= newcoloring % self[COLORS]
                newcoloring += c
                yield newcoloring
