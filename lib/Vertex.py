#!/usr/bin/env python3

#import graph_tool as gt
from pathlib import Path
from collections import defaultdict
import typing


def vectorize(funct: typing.Callable) -> typing.Callable:
    '''
    makes a function take a list as an argument and returns a list
    after calling the function on each element of the list
    '''
    def vectorized(*args):
        return [funct(arg) for arg in arglist]

    return vectorized


class Vertex:#(gt.Vertex):
    attrs = None
    neighbors = None

    def __init__(self, *args, **kwargs):
        # super().__init__(*args)
        self.attrs = defaultdict(None)
        self.neighbors = set()

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


    def add_neighbors(self, *vertices: typing.List[__name__]):
        '''
        adds vertices to self's neighboring vertices
        '''
        for v in vertices:
            self.neighbors.add(v)
