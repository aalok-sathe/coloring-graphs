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

BaseVertex::
BaseVertex()
	: depth(-1), next_neighbor(neighbors.begin())
{}

BaseVertex::
BaseVertex(long name_)
	: name(_name), depth(-1), next_neighbor(neighbors.begin())
{}

Vertex::
~Vertex()
{}


void
Vertex::
add_neighbor(Vertex& other)
{
    neighbors.push_back(other.get_name());
}

Vertex*
BaseVertex::
get_next_neighbor(Graph* g)
{
    return next_neighbor++;
}

Vertex*
ColoringVertex::
get_next_neighbor(Graph* g)
{

}

int
Vertex::lp(Graph* g)
{

}

bool
Vertex::
check_for_cut()
{

}







#endif
