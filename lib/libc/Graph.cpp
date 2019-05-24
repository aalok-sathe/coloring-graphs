#ifndef __GRAPH_CPP__
#define __GRAPH_CPP__

#include "Graph.h"


Graph::
Graph() {}

Graph::
~Graph() {}

void
Graph::
load_txt(string path)
{
    ifstream file(path);
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

#endif
