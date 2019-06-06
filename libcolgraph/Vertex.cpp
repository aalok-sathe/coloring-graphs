#ifndef __VERTEX_CPP__
#define __VERTEX_CPP__

#include "Vertex.h"


/*******************************************************************************
***************************** VERTEX *******************************************
*******************************************************************************/

Vertex::
Vertex() {}

Vertex::
Vertex(long name_)
    : name(name_), nt(new VertexNeighborIterator())
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
    // std::cout << 'get_name' << name << std::endl;
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

VertexNeighborIterator*
Vertex::
get_neighbors()
{
    std::cout << "Invoking get_neighbors" << std::endl;
    return this->__iter__();
}


VertexNeighborIterator*
Vertex::
__iter__()
{
    std::cout << "Invoking incorrect method" << std::endl;
    std::exit(1);
    return new VertexNeighborIterator({ neighbors.begin(),
                                               neighbors.size() });
}


/*******************************************************************************
***************************** ColoringVertex ***********************************
*******************************************************************************/


ColoringVertex::
ColoringVertex(long name_, int k, ColoringGraph* graph_)
    : Vertex(name_), colors(k), graph(graph_)
{}


VertexNeighborIterator*
ColoringVertex::
get_neighbors()
{
    std::cout << "iterator initialized" << std::endl;

    return __iter__();
}


VertexNeighborIterator*
ColoringVertex::
__iter__()
{
    return new ColoringVertexNeighborIterator({ name, graph, colors });
}


/*******************************************************************************
***************************** VertexNeighborIterator ***************************
*******************************************************************************/

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

VertexNeighborIterator*
VertexNeighborIterator::
__iter__()
{
    return this;
}


/*******************************************************************************
********************** ColoringVertexNeighborIterator **************************
*******************************************************************************/

ColoringVertexNeighborIterator::
ColoringVertexNeighborIterator(long name_, ColoringGraph* graph_, int colors_)
: name(name_), graph(graph_), colors(colors_)
{
    positionctr = 0;
    colorctr = 0;
    remaining = graph->base->size() * colors;
}


long
ColoringVertexNeighborIterator::
next()
{
    if (not remaining--)
    {
        std::cout << "iterator exhausted" << std::endl;

        positionctr = 0;
        colorctr = 0;
        remaining = graph->size() * colors;
        throw std::out_of_range("");
    }

    std::cout << "beginning loopity loop" << std::endl;

    // operate the nested for-loop manually
    loopanchor:
    if (positionctr+1 < graph->base->size() and colorctr >= colors)
    {
        positionctr++;
        colorctr = 0;
    }
    else if (positionctr < graph->base->size() and colorctr+1 < colors)
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
    if (true)
        throw std::logic_error("not implemented");
    return (this->remaining > 0);
}



#endif
