#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <set>
#include <cstddef>
#include <stdexcept>
#include <math.h>

#include "Graph.h"
#include "GraphTemplates.h"

class Vertex;
class BaseVertex;
class ColoringVertex;
template <typename V> class Graph;
class BaseGraph;
class ColoringGraph;


class BaseVertexNeighborIterator : public VertexNeighborIterator<BaseVertex>
{
    public:
        std::set<long>::iterator it;
        long len;

        BaseVertexNeighborIterator() {};
        BaseVertexNeighborIterator(std::set<long>::iterator it_, long len_);

        long next() override;

        bool hasnext() override;
};

class ColoringVertexNeighborIterator : public VertexNeighborIterator<ColoringVertex>
{
    public:
        long name;
        int colors;
        ColoringGraph* graph;

        long remaining;
        int positionctr;
        int colorctr;

        ColoringVertexNeighborIterator() {};
        ColoringVertexNeighborIterator(long name_, int colors_, ColoringGraph* graph_);

        // ~ColoringVertexNeighborIterator() {};

        long next() override;

        bool hasnext() override;

};


class Vertex
{
    public:
        long name;

        Vertex() {};
        Vertex(long name_);

        virtual ~Vertex();

        virtual void add_neighbor(Vertex& other) {};

        bool operator==(const Vertex& other);

        virtual long get_name() const;
};


class BaseVertex : public Vertex
{
    public:
        BaseVertexNeighborIterator* nt;
        std::set<long> neighbors;

        BaseVertex() {};
        BaseVertex(long name_);

        void add_neighbor(Vertex& other);

        virtual long get_next_neighbor();

        BaseVertexNeighborIterator* __iter__();
        BaseVertexNeighborIterator* get_neighbors();
};


class ColoringVertex : public Vertex
{
    public:
        int colors;
        ColoringGraph* graph;
        ColoringVertexNeighborIterator* nt;

        ColoringVertex(long name_, int k, ColoringGraph* graph_);

        ColoringVertexNeighborIterator* __iter__();
        ColoringVertexNeighborIterator* get_neighbors();
};

#endif
