#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <set>
#include <cstddef>
#include <stdexcept>
#include <math.h>

#include "Graph.h"

class Vertex;
class ColoringVertex;
template <typename V> class Graph;
class BaseGraph;
class ColoringGraph;

// TODO: make it a class
struct VertexNeighborIterator
{
    public:
        std::set<long>::iterator it;
        long len;

        ~VertexNeighborIterator() {};

        long next();
        long __next__();

        bool hasnext();

        VertexNeighborIterator* __iter__();
};

struct ColoringVertexNeighborIterator : public VertexNeighborIterator
{
    public:
        long name;
        ColoringGraph* graph;
        int colors;

        long remaining;
        int positionctr;
        int colorctr;

        // ColoringVertexNeighborIterator() {};
        ColoringVertexNeighborIterator(long name_, ColoringGraph* graph_, int colors_);

        // ~ColoringVertexNeighborIterator() {};

        long next();

        bool hasnext();

};

class Vertex
{
    public:
        long name;
        std::set<long> neighbors;
        VertexNeighborIterator* nt;

        Vertex();
        Vertex(long name_);

        ~Vertex();

        bool operator==(const Vertex& other);

        long get_name() const;

        void add_neighbor(Vertex& other);

        long get_next_neighbor();

        virtual VertexNeighborIterator* __iter__();
        virtual VertexNeighborIterator* get_neighbors();
};


class ColoringVertex : public Vertex
{
    public:
        int colors;
        ColoringGraph* graph;
        ColoringVertexNeighborIterator* nt;

        ColoringVertex(long name_, int k, ColoringGraph* graph_);

        VertexNeighborIterator* __iter__() override;
        VertexNeighborIterator* get_neighbors() override;
};

#endif
