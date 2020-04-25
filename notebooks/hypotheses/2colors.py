#!/usr/bin/env python3

from pathlib import Path
from glob import glob
from tqdm import tqdm
from hypothesis import Hypothesis, gather_tests
import libcolgraph as lcg

@gather_tests
class HypercubeHypothesis(Hypothesis):
    name = 'only 2 colors within a polyp'
    k = 4

    def test_2colors_only(self, g):
        # this test tests whether
        cg = g.build_coloring_graph(self.k)
        mcg = cg.tarjans()

        mship = mcg.identify_mothership()
        for mv in mcg.get_vertices():
            if mv.get_name() == mship or len(mv)/len(cg) >=.85: continue
            verts = [*mv.get_vertices()]
            cols = cg.get_possible_colors(verts)
            for tup in cols:
                if len(tup) > 2: return False
        return True


if __name__ == '__main__':
    hyp = HypercubeHypothesis()
    directories = ['../bigpolyp', '../discovered']
    for prefix in directories:
        graphs = []
        for graph in tqdm(glob(prefix + '/*/*k={}*.txt'.format(hyp.k))):
            graph = Path(graph)
            bg = lcg.BaseGraph()
            bg.path = str(graph)
            bg.load_txt(bg.path)
            graphs += [bg]
        hyp.find_counterexample(graphs)
