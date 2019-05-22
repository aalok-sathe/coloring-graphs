#!/usr/bin/env python3

#import graph_tool as gt
from pathlib import Path
from collections import defaultdict
import typing

# vertex attributes
ID = 'id'
COLOR = 'color'
NAME = 'name'

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


        def add_neighbors(self, *vertices: typing.Container[__name__]):
            '''
            adds vertices to self's neighboring vertices
            '''
            raise NotImplementedError('no support to add neighbors to a '
                                      'ColoringVertex. please read the docs')


        def get_possible_neighbors(self, k: int):
            '''

            '''
