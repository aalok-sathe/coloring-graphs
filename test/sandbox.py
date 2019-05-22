#!/usr/bin/env python3

import unittest
from pathlib import Path
import argparse
import random
import sys
sys.path.append(str((Path(__file__).parent.resolve() / '..').resolve()))
from lib import *

if __name__ == '__main__':
    rel = Path(__file__).parent
    graph = Graph.BaseGraph()
    graph.load_txt(rel / 'bipartite_test_graph0.in')
    colgraph = graph.build_coloring_graph(3)
