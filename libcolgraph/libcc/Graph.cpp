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
    std::string path_ = std::string(path);
    std::ifstream file(path_);
    int n;
    file >> n;

    for (int i=0; i<n; i++)
        vertices.insert(std::map<int, Vertex>::value_type(i, Vertex()));

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
    Vertex v;
    vertices.insert(std::pair<long,Vertex>(name,v));
}


std::map<long, Vertex>::iterator
Graph::
get_vertices()
{

}

MetaGraph::MetaGraph()
{

}

MetaGraph::~MetaGraph()
{

}


#endif
