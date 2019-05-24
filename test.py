#!/usr/bin/env python3

print('INFO: trying to import compiled shared library object "libcolgraph"')
try:
    import libcolgraph
except ImportError:
    raise
print()


print('INFO: listing all members of this module')
print(dir(libcolgraph))
print()


print('INFO: trying to initialize the c++ Graph::Graph object in python!')
try:
    cppgraph = libcolgraph.Graph()
    print(cppgraph)
except Exception:
    raise
print()


testinp = 'test/input/g1.in' # converts to cpp type char*
print('INFO: loading graph from test input file %s' % testinp)
try:
    cppgraph.load_txt(testinp)
except Exception:
    raise
print()


print('INFO: checking size of graph after loading %s' % testinp)
try:
    print(cppgraph.size())
except Exception:
    raise
print()


print('INFO: trying to inherit a pure python class from cpp Graph::Graph')
class DummyGraph(libcolgraph.Graph):
    def __init__(self):
        super().__init__()

dg = DummyGraph()
print(dg)
dg.load_txt(testinp)
print('INFO: size=', dg.size())
print()
