#!/usr/bin/env python3

from libcolgraph import *


#_ = BaseGraph()
print('attempting to instantiate basegraph')
bg = BaseGraph()
print('attempting to load in a graph')
bg.load_txt('./test/input/bipartite_test_graph0.in')

v = bg.get_some_vertex()
print('some vertex of g: ', v, v.get_name())
print('trying to get its neighbors using', v.get_neighbors())
l = [*v.get_neighbors()]
print('its neighbors: ', l)

cg = bg.build_coloring_graph(3)

print('g, cg: \n', bg, len(bg), '\n', cg, len(cg))

v = cg.get_some_vertex()
print('some vertex of cg: ', v, v.get_name(), v.get_neighbors())

# v = cg.get_vertex(364)
# print('some vertex of cg: ', v.get_name())


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
