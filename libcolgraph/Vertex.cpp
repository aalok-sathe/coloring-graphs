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
	: next_neighbor(neighbors.begin())
{}

BaseVertex::
BaseVertex(long name_)
	: next_neighbor(neighbors.begin())
{}

Vertex::
~Vertex()
{}


void
BaseVertex::
add_neighbor(Vertex& other)
{
    neighbors.push_back(other.name);
}

long
BaseVertex::
get_next_neighbor(Graph* g)
{
    return *next_neighbor++;
}

long
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
