#ifndef __VERTEX_CPP__
#define __VERTEX_CPP__

#include "Vertex.h"

Vertex::
Vertex() {}

Vertex::
Vertex(long name_)
    : name(name_)
{}

Vertex::
~Vertex()
{}

bool
Vertex::
operator==(const Vertex& other)
{
    return name == other.get_name();
}

long
Vertex::
get_name() const
{
    return name;
}

void
Vertex::
add_neighbor(Vertex& other)
{
    neighbors.insert(other.get_name());
}

struct VertexNeighborIterator
Vertex::
get_neighbors()
{
    return __iter__();
}


struct VertexNeighborIterator
Vertex::
__iter__()
{
    struct VertexNeighborIterator ret = { neighbors.begin(), neighbors.size() };
    return ret;
}


#endif
