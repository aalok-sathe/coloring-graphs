#!/usr/bin/env python3

import unittest
from pathlib import Path
import argparse
import random
import sys
from matplotlib import pyplot as plt
import networkx as nx

import sys
sys.path.append(str((Path(__file__).parent.resolve() / '..').resolve()))
from lib import *

try:
    test_file = Path(*Path(sys.argv[1]).parts[1:])
except IndexError:
    # test_file = 'input/g1.in'
    test_file = 'input/bipartite_test_graph0.in'


if __name__ == '__main__':
    rel = Path(__file__).parent
    graph = Graph.BaseGraph()
    graph.load_txt(rel / test_file)
    colgraph = graph.build_coloring_graph(3)

    draw_fn = nx.draw
    kwargs = dict(with_labels=1, node_size=2048, font_size=10)

    plt.subplot(1, 2, 1)
    plt.xlabel(graph.__class__.__name__)
    graph.draw(draw_fn, **kwargs)

    plt.subplot(1, 2, 2)
    plt.xlabel(colgraph.__class__.__name__)
    colgraph.draw(draw_fn, **kwargs)

    plt.tight_layout()
    plt.show()
