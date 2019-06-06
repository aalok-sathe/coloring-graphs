#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <cstddef>
#include <stdexcept>
#include <fstream>
#include "Vertex.h"
#include "MetaGraph.h"


/*
 *  the OG graph class
 */
class Graph
{

    public:
        std::map<long, Vertex> vertices;

        Graph();
        ~Graph();

        

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
        void load_txt(char* path);

        void add_vertex(long name);

        MetaGraph Tarjans();


        
        // long size();
        //
        // void add_vertex(long name);
        //
        // Vertex& get_vertex(long name);

        // std::map<long, Vertex>::iterator get_vertices();
};


class ColoringGraph : public Graph
{
        

    public:
        Graph* base;
        MetaGraph Tarjans();

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
