#!/usr/bin/env python3

import unittest
import Graph


    
class TestBaseGraph(unittest.TestCase):
    
    def setUp(self):
        self.graph = Graph.BaseGraph()

    def test_construction(self):
        self.assertTrue(not self.graph.is_directed())

    def test_addvertex(self):
        return True

class TestColoringGraph(TestBaseGraph):

    def setUp(self):
        self.graph = Graph.ColoringGraph()



if __name__ == '__main__':
    unittest.main(verbosity=2)
