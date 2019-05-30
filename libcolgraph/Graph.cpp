#ifndef __GRAPH_CPP__
#define __GRAPH_CPP__

#include "Graph.h"
#include <list>
#include <map>


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
    vertices.insert(std::unordered_map<int, Vertex>::value_type(name, Vertex()));
}


Vertex&
Graph::
get_vertex(long name = NULL)
{
    if (name == NULL)
        for (auto& item : vertices)
            return item.second;
    // try
        return vertices.at(name);
    // catch(const std::out_of_range& oor)
}


// std::map<long, Vertex>::iterator
// Graph::
// get_vertices()
// {
//     // TODO
// }

MetaGraph
Graph::Tarjans()
{

    //*****************************
    // Declare helper variables and structures

    MetaGraph metagraph;
    std::list<Vertex>::iterator current, temp;
    Vertex root;
    Vertex *child;
    std::list<Vertex> list;

    //*****************************
    // Main body of the method


    // For loop ensures all vertices
    // will be processed in case the
    // graph is disconnected
    for (auto& [name, vertex] : this->vertices)
    {
        list.clear();

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

        while(true)
        {
            child = current->get_next_neighbor(this);

            if (child != NULL)
            {   
                // if the DFS found another child,
                // go down that path
                list.push_back(*child);
                child->parent = current;
                child->depth = current->depth + 1;
                ++current;
            }

            else //if (child == NULL)
            {
                // Break if the root has no more children
                if (current->name == root.name) {break;}

                // Compute lowpoint
                current->lowpoint = current->lp(this);
                
                if (current->parent->name == root.name ||
                    current->lowpoint >= current->parent->depth)
                {
                    // If DFS ever gets back to the
                    // root, everything left in the list
                    // is a biconnected component

                    // Also, if the parent is a cut vertex,
                    // everything in the list after current
                    // is a biconnected component
                    MetaVertex m;
                    m.vertices.push_back(*(current->parent));
                    temp = current->parent;
                    m.vertices.splice(m.vertices.begin(), list, current, list.end());
                    metagraph.add_vertex(m);
                    current = temp;
                }
                else {current = current->parent;}

            } //end of main if-else
        
        } // end of while loop

    } // end of main for loop
}



#endif
