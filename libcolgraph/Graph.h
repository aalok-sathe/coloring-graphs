#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <cstddef>
#include <stdexcept>
#include <fstream>
#include "Vertex.h"
#include "MetaGraph.h"

class Vertex;
/*
 *  the OG graph class
 */
class Graph
{
    private:

    protected:
    public:
        std::unordered_map<long, Vertex> vertices;

    public:

        Graph();
        ~Graph();

        void load_txt(char* path);

        long size();

        void add_vertex(long name);

        Vertex& get_vertex(long name);

        // std::map<long, Vertex>::iterator get_vertices();

        MetaGraph Tarjans();


};


class BaseGraph : public Graph
{
    private:

    protected:

    public:

        // void load_txt(char* path);
        //
        // long size();
        //
        // void add_vertex(long name);
        //
        // Vertex& get_vertex(long name);

        // std::map<long, Vertex>::iterator get_vertices();
};


class ColoringGraph : public Graph
{
    private:

    protected:
        Graph* base;

    public:

        // void load_txt(char* path);
        //
        // long size();
        //
        // void add_vertex(long name);
        //
        // Vertex& get_vertex(long name);

        // std::map<long, Vertex>::iterator get_vertices();
};




#endif
