#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <cstddef>
// #include <string>
#include <fstream>
#include "Vertex.h"
#include "MetaGraph.h"


/*
 *  the OG graph class
 */
class Graph
{
    private:

    protected:
    public:
        std::map<long, Vertex> vertices;

    public:

        Graph();
        ~Graph();

        void load_txt(char* path);

        long size();

        void add_vertex(long name);

        Vertex& get_vertex(long name);

        std::map<long, Vertex>::iterator get_vertices();

        MetaGraph Tarjans();


};


class BaseGraph : Graph
{
    private:

    protected:

    public:
};


class ColoringGraph : Graph
{
    private:

    protected:
        Graph* base;

    public:
};




#endif
