#ifndef __GRAPH_CPP__
#define __GRAPH_CPP__

#include "Graph.h"
#include <list>


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

MetaGraph
Graph::Tarjans()
{

    //*****************************
    // Declare helper variables and structures

    MetaGraph metagraph; //to be returned eventually
    std::list<Vertex>::iterator current;
    Vertex root, child;
    std::list<Vertex> list;


    //*****************************
    // Main body of the method


    // For loop ensures all vertices
    // will be processed in case the
    // graph is disconnected
    for (auto& [name, vertex] : this->vertices)
    {
        if(vertex.depth == -1)
        {   
            // If vertex has not been
            // visited, set up that
            // vertex as a root for DFS
            root = vertex;
            vertex.depth = 0;
            list.push_back(vertex);
            current = list.begin();
        }

        // do
        // {

        // }
        // while ();
    }
}


#endif
