#!/usr/bin/env python3

from libcolgraph import *
from tqdm import tqdm
import random
import argparse
import networkx as nx
from collections import defaultdict
from pathlib import Path

# TODO optimize by adding random edges until connected

#def get_maximal_connected(v, p, require_connected=True):
#    assert 1 >= p >= 0
#    iters = 0
#    bg = BaseGraph()
#    bg.generate_random(v, 0)
#    if v in {0, 1}: return bg
#    bg.tarjans()
#    while not bg.is_connected():
#        
#        bg.tarjans()
#
#    return None


#def get_maximal_connected(v, p=.7, maxiter, require_connected=True):
#    assert 1 >= p > 0
#    iters = 0
#    while iters < min(maxiter, 100):
#        iters += 1
#        bg = BaseGraph()
#        bg.generate_random(v, p)
#        bg.tarjans()
#        if not require_connected or bg.is_connected():
#            return bg
#
#    return None




def get_random_connected(v, p, maxiter, require_connected=True):
    assert 1 >= p > 0
    iters = 0
    while iters < min(maxiter, 1000):
        iters += 1
        bg = BaseGraph()
        bg.generate_random(v, p)
        bg.tarjans()
        if not require_connected or bg.is_connected():
            return bg
    return None


def discover(v=7, p=.5, k=4, numiter=100, args=None):
    discovered = []
    for i in tqdm(range(numiter)):
        try:
            bg = get_random_connected(v, p, numiter, 
                                      not args.allow_disconnected)
        except ValueError: continue
        if not bg: continue
        cg = bg.build_coloring_graph(k)
        mcg = cg.tarjans()
        if cg.is_connected() and not cg.is_biconnected():
            discovered += [bg]

    return discovered


def to_matrix_str(g):    
    ''' 
    '''
    lookup = dict()                                            
    for i, v in enumerate(g.get_vertices()):                   
        lookup[v.get_name()] = i                               
                                                               
    ret = '%d\n' % len(g)                                      
                                                                                                                        
    mat = [['0' for _ in range(len(g))] for _ in range(len(g))]
    for v in g.get_vertices():                                 
        for n in v.get_neighbors():                            
            mat[lookup[v.get_name()]][lookup[n]] = '1'         
            mat[lookup[n]][lookup[v.get_name()]] = '1'         
                                                               
    for line in mat:                                           
        ret += ' '.join(line) + '\n'                           
                                                               
    return ret


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


def main():
    '''
    '''
    parser = argparse.ArgumentParser()
    parser.add_argument('-d', '--dry-run', action='store_true',
                        help='whether to run the discovery but not save it?',
                        default=False)
    parser.add_argument('-n', '--iterations', type=int, default=1000,
                        help='number of iterations to run the discovery for')
    parser.add_argument('-k', '--colors', type=int, default=4,
                        help='number of colors to use [default: 4]')
    parser.add_argument('-v', '--vertices', type=int, default=7,
                        help='number of vertices in initial ErdosReyni call')
    parser.add_argument('-p', '--probability', type=float, default=.5,
                        help='probability of edges between vertices')
    parser.add_argument('-o', '--outputdir', type=str, default='discovered',
		        help='sets the output directory relative to current '
		             'to output the discovered basegraphs in')
    parser.add_argument('-i', '--no-isomorphism', action='store_true',
                        help='don\'t check for graph isomorphism when saving '
			     'to save time even if that causes duplicate '
                             'basegraphs?', default=False)
    parser.add_argument('-c', '--allow-disconnected', action='store_true',
                        help='not require the random base graph to be connected',
                        default=False)
    parser.add_argument('-s', '--min-polyp-size', type=int, default=1,
                        help='the minimum size polyps must be to consider this '
                             'graph in our discovery')
    args = parser.parse_args()


    k, v, p = args.colors, args.vertices, args.probability
    polypbgs = discover(v, p, k, numiter=args.iterations, args=args)
    graphs = defaultdict(list)
    for g in polypbgs:
        cg = g.build_coloring_graph(args.colors)
        mcg = cg.tarjans()
        mship = mcg.identify_mothership()
        for mv in mcg.get_vertices():
            if mv.get_name() == mship: continue
            elif mv.size() >= 1+args.min_polyp_size and mv.size()/len(cg) < .85: 
                break
        else:
            continue
        print(mv, 'len(cg)={}'.format(len(cg)))
        g.polypsize = len(mv)
        if not args.no_isomorphism:
            graphs[cg.size()] = g
        else:
            graphs[cg.size()] += [g]
	

    print('Found %d uniques'%len(graphs))

    for i, (n, g) in enumerate(graphs.items()):
        name = './{}/{}/{}/v={}_k={}__p={}_cg={}_{}.txt'
        path = Path(name.format(args.outputdir, k, v,v, k, p, n, g.polypsize))
        if not path.exists(): 
            Path(path.parent).mkdir(parents=1, exist_ok=1)
        with open(str(path), 'w') as f:
            if not args.dry_run: f.write(to_matrix_str(g))
            else: print('dry-writing to', f)


if __name__ == '__main__':
    main()
    
