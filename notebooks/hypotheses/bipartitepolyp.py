#!/usr/bin/env python3

from pathlib import Path
from glob import glob
from tqdm import tqdm
from hypothesis import Hypothesis, gather_tests
import libcolgraph as lcg
import networkx as nx

def make_nx(g):
    '''
    returns a NetworkX graph from g
    '''
    G = nx.Graph()
    # G.add_nodes_from(self.vertices.keys())
    for v in g.get_vertices():
        G.add_node(v.get_name())
        for nbr in v.get_neighbors():
            G.add_edge(v.get_name(), nbr)
            # G.add_edge(nbr, v.get_name())
    return G



@gather_tests
class BipartitePolypHypothesis(Hypothesis):
    name = 'polyp can only ever be bipartite'
    k = 4

    def test_bipartite_polyp(self, g):
        # this test tests whether
        cg = g.build_coloring_graph(self.k)
        mcg = cg.tarjans()

        mship = mcg.identify_mothership()
        for mv in mcg.get_vertices():
            if mv.get_name() != mship and len(mv)/len(cg) >=.85: return None
        rcg = mcg.rebuild_partial_graph()
        rcg_ = make_nx(rcg)
        bg = lcg.BaseGraph()
        bg.load_from_nx(rcg_)
        cg_ = bg.build_coloring_graph(2)
        return len(cg) > 0


if __name__ == '__main__':
    hyp = BipartitePolypHypothesis()
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
