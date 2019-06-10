#ifndef __VERTEX_CPP__
#define __VERTEX_CPP__

#include <string>
#include <sstream>
#include "Vertex.h"


/*******************************************************************************
***************************** VERTEX *******************************************
*******************************************************************************/


Vertex::
Vertex(long name_)
    : name(name_) //, nt(new VertexNeighborIterator<Vertex>())
{}

Vertex::
~Vertex()
{}

// const char*
// Vertex::
// __repr__()
// {
//     std::stringstream repr;
//     repr << "object of base class Vertex; ";
//     repr << "with name: " << name << "; ";
//     std::string reprstr = repr.str();
//     return reprstr.c_str();
// }
//
//
// const char*
// Vertex::
// __str__()
// {
//     std::stringstream repr;
//     repr << name;
//     std::string reprstr = repr.str();
//     return reprstr.c_str();
// }

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


/*******************************************************************************
****************************** BASEVERTEX **************************************
*******************************************************************************/

BaseVertex::
BaseVertex(long name_)
    : Vertex(name_), nt(new BaseVertexNeighborIterator())
{}


void
BaseVertex::
add_neighbor(Vertex& other)
{
    neighbors.insert(other.get_name());
    delete nt;
    nt = new BaseVertexNeighborIterator(neighbors.begin(),
                                        (long)neighbors.size());
}

long
BaseVertex::
get_next_neighbor()
{
    return nt->next();
}

void
BaseVertex::
reset_neighbor_track()
{
    delete nt;
    nt = new BaseVertexNeighborIterator(neighbors.begin(),
                                        (long)neighbors.size());
}


BaseVertexNeighborIterator*
BaseVertex::
get_neighbors()
{
    return this->__iter__();
}


BaseVertexNeighborIterator*
BaseVertex::
__iter__()
{
    return new BaseVertexNeighborIterator(neighbors.begin(),
                                          (long)neighbors.size());
}


/*******************************************************************************
***************************** ColoringVertex ***********************************
*******************************************************************************/


ColoringVertex::
ColoringVertex(long name_, int k, ColoringGraph* graph_)
    : Vertex(name_), colors(k), graph(graph_)
{
    nt = new ColoringVertexNeighborIterator(name_, k, graph_);
}


long
ColoringVertex::
get_next_neighbor()
{
    return nt->next();
}


void
ColoringVertex::
reset_neighbor_track()
{
    delete nt;
    nt = new ColoringVertexNeighborIterator(name, colors, graph);
}


ColoringVertexNeighborIterator*
ColoringVertex::
get_neighbors()
{
    return __iter__();
}


ColoringVertexNeighborIterator*
ColoringVertex::
__iter__()
{
    return new ColoringVertexNeighborIterator(name, colors, graph);
}


/*******************************************************************************
***************************** VertexNeighborIterator ***************************
*******************************************************************************/

template <typename V>
long
VertexNeighborIterator<V>::
__next__()
{
    return next();
}


template <typename V>
VertexNeighborIterator<V>*
VertexNeighborIterator<V>::
__iter__()
{
    return this;
}


/*******************************************************************************
*************************** BaseVertexNeighborIterator *************************
*******************************************************************************/


BaseVertexNeighborIterator::
BaseVertexNeighborIterator(std::set<long>::iterator it_, long len_)
    : it(it_), len(len_)
{}


long
BaseVertexNeighborIterator::
next()
{
    if (this->len--)
        return *this->it++;

    throw std::out_of_range("");
}


bool
BaseVertexNeighborIterator::
hasnext()
{
    return (this->len > 0);
}


/*******************************************************************************
********************** ColoringVertexNeighborIterator **************************
*******************************************************************************/


ColoringVertexNeighborIterator::
ColoringVertexNeighborIterator(long name_, int k, ColoringGraph* graph_)
    : name(name_), colors(k), graph(graph_)
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
        positionctr = 0;
        colorctr = 0;
        remaining = graph->size() * colors;
        throw std::out_of_range("");
    }

    long newcoloring;
    std::map<long, ColoringVertex>::iterator it;

    // std::cout << "CVNIt::next beginning loopity loop" << std::endl;

    // operate the nested for-loop manually
    loopanchor:
        // long divisor = pow(colors, (graph->size()-positionctr-1));
        long divisor = graph->precompexp[positionctr][1];

        int curcol = (name / divisor) % colors;
        if (curcol == colorctr)
            goto loopcontrol; // `continue`

        newcoloring = name;
        // long newcoloring = name / divisor;
        newcoloring -= graph->precompexp[positionctr][curcol];
        // newcoloring -= newcoloring % colors;
        newcoloring += graph->precompexp[positionctr][colorctr]; // colorctr;
        // newcoloring *= divisor;
        // newcoloring += name % divisor;

        it = graph->vertices.find(newcoloring);
        if (it == graph->vertices.end())
            goto loopcontrol; // `continue`
        else
            goto after;

    loopcontrol:
        if (positionctr+1 < graph->base->size() and colorctr >= colors)
        {
            positionctr++;
            colorctr = 0;
        }
        else if (positionctr < graph->base->size() and colorctr+1 < colors)
            colorctr++;
        else
            throw std::out_of_range("");

        goto loopanchor;

    after:
        std::cerr << name << " " << newcoloring << std::endl;
        std::cerr << "DEBUG found match! " << newcoloring << std::endl;
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
