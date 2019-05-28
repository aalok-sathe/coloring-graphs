/* example.i */
%module libcolgraph

%pythoncode %{
class Graph:
    def __len__(self):
        return self.size()
    def __getattr__(self, name):
        return self.get_attribute(name)
    def __getattribute__(self, name):
        return self.get_vertex(name)

class BaseGraph(Graph):
    def __len__(self):
        return self.size()

class Vertex:
    def __getattr__(self, name):
        return self.get_attribute(name)
    def __getattribute__(self, name):
        return None
%}

%inline %{
    #include "Graph.h"
    #include "Vertex.h"
%}

%include "Graph.h"
%include "Vertex.h"
