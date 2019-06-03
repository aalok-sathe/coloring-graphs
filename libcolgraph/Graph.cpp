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
    return vertices.at(name);
}


const struct GraphVertexIterator*
Graph::
get_vertices()
{
    return __iter__();
}


const struct GraphVertexIterator*
Graph::
__iter__()
{
    // struct GraphVertexIterator* ret;
    return new struct GraphVertexIterator({ vertices.begin(), size() });
    // return ret;
}


ColoringGraph::
ColoringGraph(int k)
    : colors(k)
{}


Vertex
GraphVertexIterator::
next()
{
    if (this->len--)
        return this->it++->second;

    throw std::out_of_range("");
}


Vertex
GraphVertexIterator::
__next__()
{
    return next();
}


bool
GraphVertexIterator::
hasnext()
{
    return (this->len > 0);
}


struct GraphVertexIterator*
GraphVertexIterator::
__iter__()
{
    return this;
}


#endif
