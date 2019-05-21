#!/usr/bin/env python3

import graph_tool as gt
from pathlib import Path
from collections import defaultdict

class Vertex(gt.Vertex):
    attrs = None

    def __init__(self, *args):
        super().__init__(*args)
        self.attrs = defaultdict(None)

    def __getitem__(self, key):
        return self.attrs[key]

    def __setitem__(self, key, value)
        self.attrs[key] = value
