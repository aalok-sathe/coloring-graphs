#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <unordered_set>
#include <list>
#include <cstddef>
#include <stdexcept>
#include <math.h>
#include <limits.h>

#include "Graph.h"
#include "GraphTemplates.h"

class Vertex;
class BaseVertex;
class ColoringVertex;
class MetaVertex;
template <typename V> class Graph;
class BaseGraph;
class ColoringGraph;
class MetaGraph;


class BaseVertexNeighborIterator : public VertexNeighborIterator<BaseVertex>
{
    public:
        std::unordered_set<long>::iterator it;
        long len;

        BaseVertexNeighborIterator() {};
        BaseVertexNeighborIterator(std::unordered_set<long>::iterator it_, long len_);

        long next() override;

        bool hasnext() override;
};

class ColoringVertexNeighborIterator : public VertexNeighborIterator<ColoringVertex>
{
    public:
        long name;
        int colors;
        ColoringGraph* graph;

        // long remaining;
        int outerpos;
        int positionctr;
        int colorctr;

        ColoringVertexNeighborIterator() {};
        ColoringVertexNeighborIterator(long name_, int colors_, ColoringGraph* graph_);

        // ~ColoringVertexNeighborIterator() {};

        long next() override;

        bool hasnext() override;

};

class MetaVertexNeighborIterator : public VertexNeighborIterator<MetaVertex>
{
    public:
        std::unordered_set<long>::iterator it;
        long len;

        MetaVertexNeighborIterator() {};
        MetaVertexNeighborIterator(std::unordered_set<long>::iterator it_, long len_);

        long next() override;

        bool hasnext() override;
};


class Vertex
{
    public:
        long name;

        int depth;
        int lowpoint;
        std::list<long>::iterator parent;

        Vertex() {};
        Vertex(long name_);

        virtual ~Vertex();

        // virtual const char* __repr__();
        // virtual const char* __str__();

        bool operator==(const Vertex& other);

        virtual long get_next_neighbor() = 0;
        virtual void reset_neighbor_track() = 0;

        virtual long get_name() const;

        // virtual VertexNeighborIterator<Vertex>* __iter__() = 0;
        // virtual VertexNeighborIterator<Vertex>* get_neighbors() = 0;
};


class BaseVertex : public Vertex
{
    public:
        std::unordered_set<long> neighbors;
        BaseVertexNeighborIterator* nt;

        BaseVertex() {};
        BaseVertex(long name_);

        void add_neighbor(Vertex& other);

        long get_next_neighbor() override;
        void reset_neighbor_track() override;

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

        long get_next_neighbor() override;
        void reset_neighbor_track() override;

        ColoringVertexNeighborIterator* __iter__();
        ColoringVertexNeighborIterator* get_neighbors();
};



class MetaVertex : public Vertex
{
    public:
        // long name;
        std::unordered_set<long> neighbors;
        typename std::unordered_set<long> vertices;
        // typename std::unordered_set<long> meta_neighbors ;
        // int depth;
        MetaVertexNeighborIterator* nt;
        long identity;

        MetaVertex(long name_);
        // MetaVertex(Vertex* v);

        ~MetaVertex() {};

        void add_neighbor(MetaVertex& other);

        // add to each other's neighbor list
        void connect(MetaVertex* v);
        void disconnect(MetaVertex* v);

        long get_next_neighbor() override;
        void reset_neighbor_track() override {};

        MetaVertexNeighborIterator* __iter__();
        MetaVertexNeighborIterator* get_neighbors();


};



#endif
