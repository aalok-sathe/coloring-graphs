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
Vertex::
add_neighbor(Vertex& v)
{

}

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
Vertex::
get_next_neighbor(Graph* g)
{

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
Vertex::
lp(Graph* g)
{

}

int
BaseVertex::
lp(Graph* g)
{
	int min = depth;
	Vertex next;
	for (auto& neighbor : neighbors)
	{
		next = g->vertices.find(neighbor)->second;
		
		if (next.parent->name == this->name)
		{
			min = std::min(min, next.lowpoint);
		}

		else
		
		{
			min = std::min(min, next.depth);
		}
	}
	return min;
}

int
ColoringVertex::
lp(Graph* g)
{

}







#endif
