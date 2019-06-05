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


template <typename V>
struct GraphVertexIterator
{
    public:
        typename std::map<long, V>::iterator it;
        long len;

        GraphVertexIterator<V>(typename std::map<long, V>::iterator it_, long len_)
            : it(it_), len(len_) {};
        ~GraphVertexIterator() {};

        V next();
        V __next__();

        bool hasnext();

        struct GraphVertexIterator<V>* __iter__();

};

// struct ColoringGraphVertexIterator : public GraphVertexIterator
// {
//
// };

/*
 *  the OG graph class
 */
template <typename V = Vertex>
class Graph
{
    public:
        typename std::map<long, V> vertices;

        Graph();
        // Graph(char* path);
        ~Graph();

        void load_txt(char* path);

        long size();
        long __len__() { return size(); };

        void add_vertex(long name);
        void make_edge(long a, long b);

        V& get_vertex(long name);
        V& get_some_vertex();

        const struct GraphVertexIterator<V>* __iter__();
        const struct GraphVertexIterator<V>* get_vertices();


};

template <typename V = Vertex>
class BaseGraph : public Graph<V>
{
    public:
        // BaseGraph(char* path);

        bool is_valid_coloring(long coloring, int k);

        int get_vertex_color(long coloring, long name, int k);

        ColoringGraph<ColoringVertex>* build_coloring_graph(int k);

};


template <typename V = ColoringVertex>
class ColoringGraph : public Graph<V>
{
    public:
        int colors;
        Graph* base;
        typename std::map<long, V> vertices;
        // precompexp[p][c] --> c * (COLORS ** p)
        std::vector<std::vector<long> > precompexp;

        ColoringGraph(int k, Graph* g);

        void add_vertex(long name, int k);

        const struct GraphVertexIterator<V>* __iter__();
        const struct GraphVertexIterator<V>* get_vertices();

};


#endif
