#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <string>
#include <fstream>
#include "Vertex.h"

using namespace std;

/*
 *  the OG graph class
 */
class Graph
{
    private:

    protected:
        map<long, Vertex> vertices;

    public:

        Graph();
        ~Graph();

        void load_txt(string path);

        void add_vertex(int name);

        map<long, Vertex>::iterator get_vertices();

};


class BaseGraph : Graph
{
    private:

    protected:

    public:
};


class ColoringGraph
{
    private:
        Graph* base;

    protected:

    public:
};


#endif
