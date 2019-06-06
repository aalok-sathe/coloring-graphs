#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include "Vertex.h"


class Vertex;
class ColoringVertex;
class Graph;
class BaseGraph;
class ColoringGraph;


template <typename V, typename V_iter = Vertex>
struct GraphVertexIterator
{
    public:
        typename std::map<long, V_iter>::iterator it;
        long len;

        GraphVertexIterator<V, V_iter>(typename std::map<long, V_iter>::iterator it_, long len_)
            : it(it_), len(len_) {};
        ~GraphVertexIterator() {};

        V next();
        V __next__();

        bool hasnext();

        struct GraphVertexIterator<V, V_iter>* __iter__();

};

// struct ColoringGraphVertexIterator : public GraphVertexIterator
// {
//
// };

/*
 *  the OG graph class
 */
// template <typename V = Vertex>
class Graph
{
    public:
        std::map<long, Vertex> vertices;

        Graph();
        // Graph(char* path);
        ~Graph();

        void load_txt(char* path);

        virtual long size();
        virtual long __len__() { return size(); };

        virtual void add_vertex(long name);
        void make_edge(long a, long b);

        Vertex& get_vertex(long name);
        Vertex& get_some_vertex();

        virtual const struct GraphVertexIterator<Vertex>* __iter__();
        virtual const struct GraphVertexIterator<Vertex>* get_vertices();


};

// template <typename V = Vertex>
class BaseGraph : public Graph
{
    public:
        // BaseGraph(char* path);

        bool is_valid_coloring(long coloring, int k);

        int get_vertex_color(long coloring, long name, int k);

        ColoringGraph* build_coloring_graph(int k);

};


// template <typename V = ColoringVertex>
class ColoringGraph : public Graph
{
    public:
        int colors;
        Graph* base;
        // std::map<long, ColoringVertex> vertices;
        // precompexp[p][c] --> c * (COLORS ** p)
        std::vector<std::vector<long> > precompexp;

        ColoringGraph(int k, Graph* g);

        void add_vertex(long name);

        // ColoringVertex& get_vertex(long name);
        // ColoringVertex& get_some_vertex();
        //
        // const struct GraphVertexIterator<ColoringVertex>* __iter__();
        // const struct GraphVertexIterator<ColoringVertex>* get_vertices();

};


#endif
