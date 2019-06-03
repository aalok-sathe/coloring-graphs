#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <cstddef>
#include <stdexcept>
// #include <string>
#include <fstream>
#include "Vertex.h"


class Vertex;
class ColoringVertex;
class Graph;
class BaseGraph;
class ColoringGraph;


struct GraphVertexIterator
{
    std::map<long, Vertex>::iterator it;
    long len;

    ~GraphVertexIterator() {};

    Vertex next();
    Vertex __next__();

    bool hasnext();

    struct GraphVertexIterator* __iter__();

};

/*
 *  the OG graph class
 */
class Graph
{
    public:
        std::map<long, Vertex> vertices;

        Graph();
        ~Graph();

        void load_txt(char* path);

        long size();
        long __len__() { return size(); };

        void add_vertex(long name);

        Vertex& get_vertex(long name);

        const struct GraphVertexIterator* __iter__();
        const struct GraphVertexIterator* get_vertices();

        ColoringGraph* build_coloring_graph(int k) {};

};


class BaseGraph : public Graph
{
    public:

};


class ColoringGraph : public Graph
{
    public:
        Graph* base;
        int colors;

        ColoringGraph(int k);

};


#endif
