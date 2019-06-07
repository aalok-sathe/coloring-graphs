#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include "GraphTemplates.h"
#include "Vertex.h"


class Vertex;
class ColoringVertex;
template <typename V> class Graph;
class BaseGraph;
class ColoringGraph;


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
