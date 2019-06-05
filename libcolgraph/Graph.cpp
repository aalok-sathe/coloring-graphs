#ifndef __GRAPH_CPP__
#define __GRAPH_CPP__

#include "Graph.h"


/*******************************************************************************
***************************** GRAPH ********************************************
*******************************************************************************/

Graph::
Graph() {}

// Graph::
// Graph(char* path)
// {
//     load_txt(path);
// }

Graph::
~Graph() {}


void
Graph::
load_txt(char* path)
{
    // std::string path_ = std::string(path);
    std::ifstream file(path);
    int n;
    file >> n;

    for (int i=0; i<n; i++)
        add_vertex((long)i);

    int value;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
        {
            file >> value;
            if (value)
                vertices[i].add_neighbor(vertices[j]);
        }
}


long
Graph::
size()
{
    return vertices.size();
}


void
Graph::
add_vertex(long name)
{
    Vertex v(name);
    vertices.insert(std::pair<long, Vertex>(name, v));
}


void
Graph::
make_edge(long a, long b)
{
    std::map<long, Vertex>::iterator it;
    Vertex va, vb;

    it = vertices.find(a);
    if (it != vertices.end())
        va = it->second;
    else
        throw std::out_of_range("");

    it = vertices.find(b);
    if (it != vertices.end())
        vb = it->second;
    else
        throw std::out_of_range("");

    va.add_neighbor(vb);
    vb.add_neighbor(va);
}


Vertex&
Graph::
get_vertex(long name)
{
    return vertices.at(name);
}


Vertex&
Graph::
get_some_vertex()
{
    for (auto& pair : vertices)
            return pair.second;
}


template<typename V>
const struct GraphVertexIterator<V>*
Graph<V>::
get_vertices()
{
    return __iter__();
}


template<typename V>
const struct GraphVertexIterator<V>*
Graph<V>::
__iter__()
{
    // struct GraphVertexIterator* ret;
    return new struct GraphVertexIterator<Vertex>({ vertices.begin(), size() });
    // return ret;
}

/*******************************************************************************
***************************** BASEGRAPH ****************************************
*******************************************************************************/


// BaseGraph::
// BaseGraph(char* path)
// {
//     load_txt(path);
// }


ColoringGraph<ColoringVertex>*
BaseGraph::
build_coloring_graph(int k)
{
    ColoringGraph<ColoringVertex>* cg = new ColoringGraph<ColoringVertex>(k, this);
    for (long coloring=0; coloring<pow(k, size()); coloring++)
        if (is_valid_coloring(coloring, k))
            cg->add_vertex(coloring, k);
        else
            continue;

    return cg;

}


int
BaseGraph::
get_vertex_color(long coloring, long name, int k)
{
    return (coloring / (long)pow(k, (size()-name-1))) % k;
}


bool
BaseGraph::
is_valid_coloring(long coloring, int k)
{
    for (auto& pair : vertices)
    {
        long vname = pair.first;
        Vertex v = pair.second;
        int vcol = get_vertex_color(coloring, vname, k);

        std::set<long>::iterator it;
        for (it = v.neighbors.begin(); it != v.neighbors.end(); it++)
            if (vcol == get_vertex_color(coloring, *it, k))
                return false;
    }

    return true;
}


/*******************************************************************************
***************************** COLORINGGRAPH ************************************
*******************************************************************************/

const struct GraphVertexIterator<ColoringVertex>*
ColoringGraph::
get_vertices()
{
    return __iter__();
}

const struct GraphVertexIterator<ColoringVertex>*
ColoringGraph::
__iter__()
{
    // struct GraphVertexIterator* ret;
    return new struct GraphVertexIterator<ColoringVertex>({ vertices.begin(), size() });
    // return ret;
}


ColoringGraph::
ColoringGraph(int k, Graph* g)
    : colors(k), base(g)
{}


void
ColoringGraph::
add_vertex(long name, int k)
{
    ColoringVertex vertex(name, k, this);
    vertices.insert(std::pair<long, ColoringVertex>(name, vertex));

    std::vector<long> v;
    for (int i=0; i<colors; v.push_back(i++*pow(colors, precompexp.size())));
    precompexp.push_back(v);
}


/*******************************************************************************
***************************** GraphVertexIterator*******************************
*******************************************************************************/


template <class V>
V
GraphVertexIterator<V>::
next()
{
    if (this->len--)
        return this->it++->second;

    throw std::out_of_range("");
}


template <class V>
V
GraphVertexIterator<V>::
__next__()
{
    return next();
}


template <class V>
bool
GraphVertexIterator<V>::
hasnext()
{
    return (this->len > 0);
}


template <class V>
struct GraphVertexIterator<V>*
GraphVertexIterator<V>::
__iter__()
{
    return this;
}

/*******************************************************************************
**************************** ColoringGraphVertexIterator ***********************
*******************************************************************************/

// Vertex
// ColoringGraphVertexIterator::
// next()
// {
//     if (this->len--)
//         return this->it++->second;
//
//     throw std::out_of_range("");
// }
//
// Vertex
// ColoringGraphVertexIterator::
// __next__()
// {
//     return next();
// }
//
// struct ColoringGraphVertexIterator*
// ColoringGraphVertexIterator::
// __iter__()
// {
//     return this;
// }


#endif
