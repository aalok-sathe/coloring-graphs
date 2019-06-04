#ifndef __VERTEX_CPP__
#define __VERTEX_CPP__

#include "Vertex.h"

Vertex::
Vertex() {}

Vertex::
Vertex(long name_)
    : name(name_), nt(new struct VertexNeighborIterator())
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
    delete nt;
    nt = new VertexNeighborIterator({ neighbors.begin(),
                                      neighbors.size() });
}

long
Vertex::
get_next_neighbor()
{
    return nt->next();
}

struct VertexNeighborIterator*
Vertex::
get_neighbors()
{
    return __iter__();
}


struct VertexNeighborIterator*
Vertex::
__iter__()
{
    return new struct VertexNeighborIterator({ neighbors.begin(),
                                               neighbors.size() });
}



long
VertexNeighborIterator::
next()
{
    if (this->len--)
        return *this->it++;

    throw std::out_of_range("");
}

long
VertexNeighborIterator::
__next__()
{
    return next();
}

bool
VertexNeighborIterator::
hasnext()
{
    return (this->len > 0);
}

struct VertexNeighborIterator*
VertexNeighborIterator::
__iter__()
{
    return this;
}


ColoringVertexNeighborIterator::
ColoringVertexNeighborIterator(long name_, ColoringGraph* graph_, int colors_)
: name(name_), graph(graph_), colors(colors_)
{
    positionctr = 0;
    colorctr = 0;
    remaining = graph->size() * colors;
}


long
ColoringVertexNeighborIterator::
next()
{
    if (not remaining--)
    {
        positionctr = 0;
        colorctr = 0;
        remaining = graph->size() * colors;
        throw std::out_of_range("");
    }

    // operate the nested for-loop manually
    loopanchor:
    if (positionctr+1 < graph->size() and colorctr >= colors)
    {
        positionctr++;
        colorctr = 0;
    }
    else if (positionctr < graph->size() and colorctr+1 < colors)
        colorctr++;
    else
        throw std::out_of_range("");

    // long divisor = pow(colors, (graph->size()-positionctr-1));
    long divisor = graph->precompexp[positionctr][1];

    int curcol = (name / divisor) % colors;
    if (curcol == colorctr)
        goto loopanchor; // `continue`

    // long newcoloring = name / divisor;
    long newcoloring = name;
    newcoloring -= graph->precompexp[positionctr][curcol];
    // newcoloring -= newcoloring % colors;
    newcoloring += graph->precompexp[positionctr][colorctr]; // colorctr;
    // newcoloring *= divisor;
    // newcoloring += name % divisor;

    return newcoloring;
}

bool
ColoringVertexNeighborIterator::
hasnext()
{
    return (this->remaining > 0);
}



#endif
