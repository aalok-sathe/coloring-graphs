#!/usr/bin/env python3

from pathlib import Path
from glob import glob
from tqdm import tqdm
from collections import defaultdict
from hypothesis import Hypothesis, gather_tests
import libcolgraph as lcg

@gather_tests
class JumpHypothesis(Hypothesis):
    name = 'no colorings to connected but not 2-connected'
    k = 2
    cgk = None # g.build_coloring_graph(self.k)
    mcgk = None # cg.tarjans()
    maxk = 6

    def test_no_jumps(self, g):

        while self.k <= self.maxk:
            cg = g.build_coloring_graph(self.k+1)
            mcg = cg.tarjans()
            
            if self.cgk is not None:
                want = self.cgk.is_biconnected()
                want = want and cg.is_connected() and not cg.is_biconnected()
                if want: 
                    print(self.k-1, self.k)
                    return False
    
            self.cgk = cg
            self.mcgk = mcg
            self.k += 1

        return True


if __name__ == '__main__':
    hyp = JumpHypothesis()
    directories = ['../bigpolyp', '../discovered']
    for prefix in directories:
        graphs = []
        for graph in tqdm(glob(prefix + '/*/*.txt')+glob(prefix + '/*/*/*.txt')):
            graph = Path(graph)
            bg = lcg.BaseGraph()
            bg.path = str(graph)
            bg.load_txt(bg.path)
            graphs += [bg]
        hyp.find_counterexample(graphs)
