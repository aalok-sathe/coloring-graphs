#!/usr/bin/env python3

import unittest
import Graph
from pathlib import Path


class TestBaseGraph(unittest.TestCase):

    def setUp(self):
        '''
        initialize
        '''
        self.graph = Graph.BaseGraph()

    def test_load_txt(self):
        '''
        tests loading graph representation from an adjacency matrix
        saved in a text file
        '''
        self.graph.load_txt('bipartite_test_graph0.in')
        with Path('bipartite_test_graph0.in').open() as f:
            n_init = int(f.readline())
            n_act = len(f.readlines())
        self.assertTrue(len(self.graph) == n_init)
        self.assertTrue(len(self.graph.get_vertices()) == n_act)

    def test_addvertex(self):
        return 0


class TestColoringGraph(TestBaseGraph):

    def setUp(self):
        self.graph = Graph.ColoringGraph()



if __name__ == '__main__':
    unittest.main(verbosity=2)
