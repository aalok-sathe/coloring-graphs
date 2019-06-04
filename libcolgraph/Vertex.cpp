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

void
BaseVertex::
add_neighbor(Vertex& other)
{
    neighbors.push_back(other.name);
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
