#!/usr/bin/env python3

import unittest
from pathlib import Path
import argparse
import sys
sys.path.append(str(Path(__file__).parent.resolve() / '..'))

import Graph

class TestBaseGraph(unittest.TestCase):

    def setUp(self):
        '''
        initialize
        '''
        self.rel = Path(__file__).parent
        self.graph = Graph.BaseGraph()

    def test_load_txt(self):
        '''
        tests loading graph representation from an adjacency matrix
        saved in a text file
        '''
        self.graph.load_txt(self.rel / 'bipartite_test_graph0.in')
        with (self.rel / Path('bipartite_test_graph0.in')).open() as f:
            n_init = int(f.readline())
            n_act = len(f.readlines())
        self.assertTrue(len(self.graph) == n_init)
        self.assertTrue(len([*self.graph.get_vertices()]) == n_act)

    def test_addvertex(self):
        return 0


class TestColoringGraph(TestBaseGraph):

    def setUp(self):
        '''
        initialize
        '''
        self.rel = Path(__file__).parent
        self.graph_ = Graph.BaseGraph()
        self.graph_.load_txt(self.rel / 'bipartite_test_graph0.in')
        self.graph = self.graph_.build_coloring_graph()

if __name__ == '__main__':
    unittest.main(verbosity=2)
