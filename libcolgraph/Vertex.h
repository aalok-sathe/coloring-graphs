#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <set>
#include <cstddef>
// #define StopIteration 1
// #include "GraphUtils.h"

// enum V_ATTR
// {
//     NAME,
//     COLOR
// };

struct VertexNeighborIterator
{
    std::set<long>::iterator it;
    long len;
    int stop_iter;

    ~VertexNeighborIterator() {};

    long __next__()
    {
        if (this->len--)
            return *(this->it++);

        throw(1);
    }

    struct VertexNeighborIterator* __iter__()
    {
        return this;
    }
};

class Vertex
{
    friend class Graph;

    private:

    protected:
        long name;
        std::set<long> neighbors;

    public:
        Vertex();
        Vertex(long name_);

        ~Vertex();

        bool operator==(const Vertex& other);

        long get_name() const;

        void add_neighbor(Vertex& other);

        struct VertexNeighborIterator __iter__();
        struct VertexNeighborIterator get_neighbors();
};


class ColoringVertex : public Vertex
{
    private:

    protected:

    public:
};

#endif
