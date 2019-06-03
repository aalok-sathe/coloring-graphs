#ifndef __GRAPH_CPP__
#define __GRAPH_CPP__

#include "Graph.h"
#include <list>
#include <map>
#include <stack>


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
    vertices.insert(std::map<int, Vertex>::value_type(name, Vertex()));
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
    std::list<Vertex>::iterator current, found_cut_vertex;
    Vertex root;
    Vertex *child;
    std::list<Vertex> list;
    std::stack<Vertex> cut_vertex_stack;

    //*****************************
    // Main body of the method


    // For loop ensures all vertices
    // will be processed in case the
    // graph is disconnected
    for (auto& [name, vertex] : this->vertices)
    {
        list.clear();
        while(!cut_vertex_stack.empty()){cut_vertex_stack.pop();}

        if (vertex.depth == -1)
        {
            // If vertex has not been
            // visited, set up that
            // vertex as a root for DFS
            root = vertex;
            vertex.depth = 0;
            list.push_back(vertex);
            current = list.begin();
        }

        while (true)
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
                    // is a biconnected component.
                    // OR
                    // If the parent is a cut vertex,
                    // everything in the list after current
                    // is a biconnected component.




                    //**********************************************
                    // Create biconnected component


                    // Store this since we'll be using it a lot
                    found_cut_vertex = current->parent;

                    // This MetaVertex will store all vertices
                    // in the biconnected component
                    MetaVertex main;

                    // Splice the vertices from the DFS list
                    // into the component
                    main.vertices.splice(main.vertices.begin(), list, current, list.end());
                    // Also add the cut vertex itself
                    main.vertices.push_back(*(found_cut_vertex));



                    //**********************************************
                    // Connect component to cut vertices

                    // Any vertices on the stack with greater
                    // depth than the cut vertex in question
                    // were found after that cut vertex.
                    // Thus, they are part of the component.
                    // So we connect them to the component.
                    while (cut_vertex_stack.top().depth > found_cut_vertex->depth)
                    {
                        MetaVertex::connect(main, cut_vertex_stack.top());
                        cut_vertex_stack.pop();
                    }


                    // This if statement creates a MetaVertex
                    // object for the cut vertex if one
                    // does not already exist.
                    if (cut_vertex_stack.top().name != found_cut_vertex->name)
                    {
                        MetaVertex cut(*found_cut_vertex);
                        MetaVertex::connect(main, cut);}

                    else { MetaVertex::connect(main, cut_vertex_stack.top()); }




                    // Add the cut vertex to the stack
                    cut_vertex_stack.push(*found_cut_vertex);
                    
                    // Add the new component to the MetaGraph
                    metagraph.add_vertex(main);

                    // The cut vertex is the parent,
                    // so we return the DFS to it
                    current = found_cut_vertex;
                }
                
                else {current = current->parent;}

            }
        
        } // end of while-loop

    } // end of main for-loop

    return metagraph;
}



#endif
