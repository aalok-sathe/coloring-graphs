#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <cstddef>
#include <stdexcept>
#include <fstream>
#include "Vertex.h"
#include "MetaGraph.h"



class Vertex;
class MetaGraph;
class MetaVertex;
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
        BaseGraph();
        ~BaseGraph();

        void load_txt(char* path);

        void save_txt(char* path);

        void add_vertex(long name);



        
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
        ColoringGraph();
        ~ColoringGraph();

        Graph* base;

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
