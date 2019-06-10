#ifndef __VERTEX_CPP__
#define __VERTEX_CPP__

#include "Vertex.h"
#include <limits.h>

Vertex::
Vertex()
	: depth(-1), lowpoint(INT_MAX)
{}

Vertex::
Vertex(long name_)
    : name(name_), depth(-1), lowpoint(INT_MAX)
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
add_neighbor(Vertex& v)
{
    neighbors.push_back(v.name);
}

void
BaseVertex::
remove_neighbor(Vertex& v)
{
    neighbors.remove(v.name);
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
BaseVertex::
lp(Graph* g)
{
	int min = depth;
	for (auto& neighbor : neighbors)
	{
		min = std::min(min, g->vertices.find(neighbor)->second.depth);
	}
	return min;
}

int
ColoringVertex::
lp(Graph* g)
{

}







#endif
