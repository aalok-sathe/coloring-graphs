#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <set>
#include <cstddef>
#include <stdexcept>
#include <math.h>

#include "Graph.h"

class Vertex;
class ColoringVertex;
class Graph;
class BaseGraph;
class ColoringGraph;


struct VertexNeighborIterator
{
    std::set<long>::iterator it;
    long len;

    ~VertexNeighborIterator() {};

    long next();
    long __next__();

    bool hasnext();

    struct VertexNeighborIterator* __iter__();
};

struct ColoringVertexNeighborIterator : public VertexNeighborIterator
{
    long name;
    ColoringGraph* graph;
    int colors;

    long remaining;
    int positionctr;
    int colorctr;

    ColoringVertexNeighborIterator() {};
    ColoringVertexNeighborIterator(long name_, ColoringGraph* graph_, int colors_);

    ~ColoringVertexNeighborIterator() {};

    long next();

    bool hasnext();

};

class Vertex
{
    friend class Graph;

    public:

        long name;
        std::set<long> neighbors;
        struct VertexNeighborIterator* nt;

        Vertex();
        Vertex(long name_);

        ~Vertex();

        bool operator==(const Vertex& other);

        long get_name() const;

        void add_neighbor(Vertex& other);

        long get_next_neighbor();

        struct VertexNeighborIterator* __iter__();
        struct VertexNeighborIterator* get_neighbors();
};


class ColoringVertex : public Vertex
{
    public:

        long name;
        struct ColoringVertexNeighborIterator* nt;
};

#endif
