#ifndef __VERTEX_CPP__
#define __VERTEX_CPP__

#include "Vertex.h"

Vertex::
Vertex()
	: depth(-1)
{}

Vertex::
Vertex(long name_)
    : name(name_), depth(-1)
{}

Vertex::
~Vertex()
{}

long
Vertex::
get_name()
{
    return name;
}

Vertex
Vertex::
get_next_neighbor()
{
    // TODO
}

void
Vertex::
add_neighbor(Vertex& other)
{
    neighbors.insert(other.get_name());
}



#endif
