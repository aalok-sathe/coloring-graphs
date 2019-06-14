#!/usr/bin/env python3

from libcolgraph import *
# from tqdm import tqdm
import networkx as nx
from pyvis.network import Network
from matplotlib import pyplot as plt

def sep(infostr=''):
    '''
    a visual separator printer
    '''
    print()
    print('='*80)
    print(infostr, '\n')


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


def nxdraw(g, draw_fn=nx.draw, **kwargs):
    '''
    helper method to draw graph using networkx
    '''
    G = make_nx(g)
    draw_fn(G, **kwargs)


def pyvisdraw(g, title='', **kwargs):
    '''
    use pyvis to draw graph
    '''
    net = Network(height='100%', width='100%', bgcolor='#222222',
                  font_color='white', **kwargs)
    # net = Network(**kwargs)
    net.barnes_hut()
    net.from_nx(make_nx(g))
    # net.show_buttons(filter_=['physics'])
    # net.toggle_physics(1)
    net.show("viz/{}_{}.html".format(title, len(g)))


########    TEST: basic instantation
sep('TEST: basic instantation'.upper())

bipartite = BaseGraph()
bipartite.load_txt('./test/input/bipartite_test_graph0.in')

bg = BaseGraph()
# bg.load_txt('./test/input/g1.in')
# bg.load_txt('in/hexmod.in')
# bg.load_txt('in/polypbg.in')
bg.load_txt('./test/input/g2.in')
#bg.load_txt('./test/input/g3.in')
# bg.load_txt('in/g.in')
# bg.load_txt('in/smolgraph.in')
# bg.load_txt('in/3ring.in')
# bg = bipartite

print('INFO: Graphs initialized')#: bipartite,bg:', bipartite, bg)



########    TEST: vertex getting
sep('TEST: vertex getting'.upper())

v = bg.get_some_vertex()
print('INFO: retrieved vertex {} of {}'.format(v, bg))
print('INFO: retrieving vertex by name `{}` of {}'.format(v.get_name(), bg))
v_ = bg.get_vertex(v.get_name())
print('INFO: new vertex retrieved {}'.format(v_))
print('INFO: `v == v_?`', v == v_)

########    TEST: vertex iteration
sep('TEST: vertex iteration'.upper())

print('INFO: printing all vertices of bg=', bg)
for v in bg.get_vertices():
    print(v)


########    TEST: vertex neighborhood
sep('TEST: vertex neighborhood'.upper())

try:
    print('INFO: getting the last vertex of bg')
    v = [*bg.get_vertices()][-1]
    print('INFO: retrieving neighbors of v=', v)
    for nbr_name in v.get_neighbors():
        print(bg.get_vertex(nbr_name))

    print('INFO: getting some neighbor of v, `n`')
    n = bg.get_vertex([*v.get_neighbors()][0])
    print('INFO: getting all neighbors of n', n)
    for nbr_name in n.get_neighbors():
        print(bg.get_vertex(nbr_name))

    print('INFO: `v.get_name() in n.get_neighbors()?`',
          v.get_name() in n.get_neighbors())
except Exception as e:
    print('\nERROR!\n', e)


########    TEST: generating a coloring graph
sep('TEST: generating a coloring graph'.upper())

k = int(input('how many colors? '))
print('INFO: bg.build_coloring_graph using k=%d'%k)
cg = bg.build_coloring_graph(k)
print('{} leads to coloring graph {}'.format(bg, cg))


########    TEST: getting a vertex of cg
# sep('TEST: getting a vertex of cg'.upper())

# try:
#     print('INFO: getting a vertex of cg')
#     v = cg.get_some_vertex()
#     print(v)
#
#     # print('INFO: getting neighbors of v', v)
#     # for n in v.get_neighbors():
#     #     print(n)
#     print('INFO: getting some neighbor of v')
#     n = cg.get_vertex([*v.get_neighbors()][0])
#     print(n)
#
#     print('INFO: `v.get_name() in n.get_neighbors()?`',
#           v.get_name() in n.get_neighbors())
# except Exception as e:
#     print('\nERROR!\n', e)


########    TEST: generating a meta base graph
sep('TEST: generating a meta base graph'.upper())

print('INFO: bg.tarjans()')
mbg = bg.tarjans()
print('{} leads to meta base graph {}'.format(bg, mbg))


########    TEST: generating a meta coloring graph
sep('TEST: generating a coloring base graph'.upper())

print('INFO: cg.tarjans()')
mcg = cg.tarjans()
print('{} leads to meta base graph {}'.format(bg, mcg))


########    TEST: visualize
sep('TEST: visualize'.upper())

kwargs = dict(with_labels=1, node_size=1024, font_size=10)

# plt.subplot(1, 2, 1)
# graphdraw(bg, **kwargs)
# plt.title(str(bg))
#
# plt.subplot(1, 2, 2)
# graphdraw(cg, **kwargs)
# plt.title(str(cg))
#
# plt.show()

pyvisdraw(bg, 'testbg')
pyvisdraw(cg, 'testcg')
pyvisdraw(mbg, 'testmbg')
pyvisdraw(mcg, 'testmcg')



# for mv in mcg.get_vertices():
#     for mv.


raise SystemExit


print('some vertex of g: ', (v), v.get_name())
print('trying to get its neighbors using', v.get_neighbors())
l = [*v.get_neighbors()]
print('its neighbors: ', l)

cg = bg.build_coloring_graph(3)

print('g, cg: \n', bg, len(bg), '\n', cg, len(cg))

v = cg.get_some_vertex()
print('some vertex of cg: ', v, v.get_name(), v.get_neighbors())

# v = cg.get_vertex(364)
# print('some vertex of cg: ', v.get_name())

for i in range(5):
    try:
        print('{} next neighbor '.format(i), v.get_next_neighbor())
    except StopIteration:
        pass
        # v.reset_neighbor_track()
        # print('{} next neighbor '.format(i), v.get_next_neighbor())


raise SystemExit
l = [*v.get_neighbors()]
print('its neighbors: ', l)

print('now all vertices and their neighbors: ')
print('g', bg.get_vertices())
for v in bg.get_vertices():
    print(v.get_neighbors())
    print(v.get_name(), [*v.get_neighbors()])
print('cg')
for v in cg.get_vertices():
    print(v.get_neighbors())
    print(v.get_name(), [*v.get_neighbors()])
