#!/usr/bin/env python3

from pathlib import Path
from glob import glob
from tqdm import tqdm
from collections import defaultdict
from hypothesis import Hypothesis, gather_tests
import libcolgraph as lcg

@gather_tests
class HypercubeHypothesis(Hypothesis):
    name = 'unique difference representation within a polyp'
    k = 4

    def test_unique_repr(self, g):
        # this test tests whether
        cg = g.build_coloring_graph(self.k)
        mcg = cg.tarjans()

        def difference(alpha, other):
            # computes difference representation string
            return tuple(int(alpha[i] != other[i]) for i in range(len(alpha)))

        
        mship = mcg.identify_mothership()
        motherverts = {*mcg.get_vertex(mship).get_vertices()}
        allcuts = {*mcg.get_cut_vertices()}
        mcg.rebuild_partial_graph()
        mothercuts = {*mcg.get_mothership_cut_vertices()}
        for mv in mcg.get_vertices():
            if mv.get_name() == mship or len(mv)/len(cg) >=.9: continue
            verts = [*mv.get_vertices()]
            thiscuts = set(verts).intersection(mothercuts)
            if len(thiscuts) != 1: continue
            try:
                this_cut = thiscuts.pop()
            except KeyError:
                continue
            others = set(verts).difference({this_cut})
            alpha = cg.get_possible_colors([this_cut])
            # print('cut colors:', alpha)
            reprs = defaultdict(set)
            #TODO
            reprs[difference(alpha, alpha)].update({alpha})
            flag = True
            for v in others:
                thiscolors = cg.get_possible_colors([v])
                diff = difference(alpha, thiscolors)
                #print ('this_colors:', thiscolors, 
                #        '\ndiff: ', diff)
                if diff in reprs: 
                    reprs[diff].update({thiscolors})
                    print (cg.get_possible_colors([v]), diff, sep='\n')
                    flag = False
                reprs[diff].update({thiscolors})
            if not flag:
                for k in reprs:
                    print(k)
                    for val in reprs[k]:
                        print('\t', val)
                return False
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
