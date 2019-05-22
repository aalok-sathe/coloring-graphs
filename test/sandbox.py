#!/usr/bin/env python3

import unittest
from pathlib import Path
import argparse
import random
import sys
sys.path.append(str((Path(__file__).parent.resolve() / '..').resolve()))
from lib import *


test_file = 'input/g2.in' # bipartite_test_graph0.in


if __name__ == '__main__':
    rel = Path(__file__).parent
    graph = Graph.BaseGraph()
    graph.load_txt(rel / test_file)
    colgraph = graph.build_coloring_graph(3)

    print(graph)
    # print(colgraph)

    for v in colgraph.get_vertices():
        print(repr(v))
        print('coloring repr: %s' % mathtools.convert_base(v[NAME], v[COLORS]))
        print('possible neighbors v: %d' % len([*v.get_possible_neighbors(len(colgraph))]))
        print('actual neighbors v: %d' % len([*colgraph.get_neighbors(v)]))
        # for nbr in colgraph.get_neighbors(v):
        #     print(repr(nbr))
        #     print('nbr coloring: %s' % mathtools.convert_base(nbr[NAME],
        #                                                       nbr[COLORS]))
        print()
