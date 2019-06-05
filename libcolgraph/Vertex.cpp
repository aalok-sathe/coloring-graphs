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

<<<<<<< HEAD
BaseVertex::
BaseVertex()
	: next_neighbor(neighbors.begin())
{}

BaseVertex::
BaseVertex(long name_)
	: next_neighbor(neighbors.begin())
{}
=======

>>>>>>> b17108357b0899ed1393deceda9536e5ec8e7878

Vertex::
~Vertex()
{}

void
BaseVertex::
add_neighbor(Vertex& other)
{
    neighbors.push_back(other.name);
}

<<<<<<< HEAD
long
BaseVertex::
get_next_neighbor(Graph* g)
{
    return *next_neighbor++;
}
=======

>>>>>>> b17108357b0899ed1393deceda9536e5ec8e7878

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
