#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <cstddef>
#include <stdexcept>
// #include <string>
#include <fstream>
#include <vector>
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
        Graph(char* path);
        ~Graph();

        void load_txt(char* path);

        long size();
        long __len__() { return size(); };

        void add_vertex(long name);
        void make_edge(long a, long b);

        Vertex& get_vertex(long name);
        Vertex& get_some_vertex();

        const struct GraphVertexIterator* __iter__();
        const struct GraphVertexIterator* get_vertices();


};


class BaseGraph : public Graph
{
    public:
        BaseGraph(char* path);

        bool is_valid_coloring(long coloring, int k);

        int get_vertex_color(long coloring, long name, int k);

        ColoringGraph* build_coloring_graph(int k);

};


class ColoringGraph : public Graph
{
    public:
        Graph* base;
        // precompexp[p][c] --> c * (COLORS ** p)
        std::vector<std::vector<long> > precompexp;
        int colors;

        ColoringGraph(int k, Graph* g);

        void add_vertex(long name);


};


#endif
