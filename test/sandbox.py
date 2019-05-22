#!/usr/bin/env python3

import unittest
from pathlib import Path
import argparse
import random
from matplotlib import pyplot as plt
import networkx as nx

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

    draw_fn = nx.draw
    kwargs = dict(with_labels=1, node_size=1000)

    plt.subplot(1, 2, 1)
    plt.xlabel(graph.__class__.__name__)
    graph.draw(draw_fn, **kwargs)

    plt.subplot(1, 2, 2)
    plt.xlabel(colgraph.__class__.__name__)
    colgraph.draw(draw_fn, **kwargs)

    plt.tight_layout()
    plt.show()
