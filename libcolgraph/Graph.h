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
template <typename V> class Graph;
class BaseGraph;
class ColoringGraph;


template <typename V>
class GraphVertexIterator
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

        class GraphVertexIterator<V>* __iter__();
};

/*
 *  the OG graph class
 */
template <typename V>
class Graph
{
    public:
        std::map<long, V> vertices;

        Graph();
        virtual ~Graph();

        virtual void load_txt(char* path) {};

        virtual long size();
        virtual long __len__() { return size(); };

        virtual void add_vertex(long name) = 0;

        virtual void make_edge(long a, long b);

        virtual V& get_vertex(long name);
        virtual V& get_some_vertex();

        virtual const GraphVertexIterator<V>* __iter__();
        virtual const GraphVertexIterator<V>* get_vertices();


};

// template <typename V = Vertex>
class BaseGraph : public Graph<Vertex>
{
    public:
        BaseGraph();

        void load_txt(char* path);

        void add_vertex(long name) override;
        // void make_edge(long a, long b);

        bool is_valid_coloring(long coloring, int k);

        int get_vertex_color(long coloring, long name, int k);

        ColoringGraph* build_coloring_graph(int k);

};


// template <typename V = ColoringVertex>
class ColoringGraph : public Graph<ColoringVertex>
{
    public:
        int colors;
        BaseGraph* base;
        // std::map<long, ColoringVertex> vertices;
        // precompexp[p][c] --> c * (COLORS ** p)
        std::vector<std::vector<long> > precompexp;

        ColoringGraph(int k, BaseGraph* bg);

        void add_vertex(long name) override;

        // ColoringVertex& get_vertex(long name);
        // ColoringVertex& get_some_vertex();
        //
        // const struct GraphVertexIterator<ColoringVertex>* __iter__();
        // const struct GraphVertexIterator<ColoringVertex>* get_vertices();

};


#endif
