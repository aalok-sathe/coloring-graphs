#ifndef __GRAPH_CPP__
#define __GRAPH_CPP__

#include "Graph.h"


Graph::
Graph() {}

Graph::
~Graph() {}


void
Graph::
load_txt(char* path)
{
    // std::string path_ = std::string(path);
    std::ifstream file(path);
    int n;
    file >> n;

    for (int i=0; i<n; i++)
        add_vertex((long)i);

    int value;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
        {
            file >> value;
            if (value)
                vertices[i].add_neighbor(vertices[j]);
        }
}


long
Graph::
size()
{
    return vertices.size();
}


void
Graph::
add_vertex(long name)
{
    Vertex v(name);
    vertices.insert(std::map<long, Vertex>::value_type(name, v));
}


Vertex&
Graph::
get_vertex(long name)
{
    // if (name == NULL)
    //     for (auto& item : vertices)
    //         return item.second;

    return vertices.at(name);
}


struct GraphVertexIterator
Graph::
get_vertices()
{
    return __iter__();
}


struct GraphVertexIterator
Graph::
__iter__()
{
    struct GraphVertexIterator ret = { vertices.begin(), size() };
    return ret;
}



#endif
