#ifndef __GRAPH_CPP__
#define __GRAPH_CPP__

// #include "GraphTemplates.h"
#include "Graph.h"


/*******************************************************************************
***************************** GRAPH ********************************************
*******************************************************************************/

template <typename V>
Graph<V>::
Graph() {}


template <typename V>
Graph<V>::
~Graph() {}


template <typename V>
long
Graph<V>::
size()
{
    return vertices.size();
}


// template <>
// void
// Graph<Vertex>::
// add_vertex(long name)
// {
//     Vertex v(name);
//     this->vertices.insert(std::pair<long, Vertex>(name, v));
// }


template <typename V>
void
Graph<V>::
make_edge(long a, long b)
{
    typename std::map<long, V>::iterator it;
    V * va, * vb;

    it = vertices.find(a);
    if (it != vertices.end())
        va = &it->second;
    else
        throw std::out_of_range("");

    it = vertices.find(b);
    if (it != vertices.end())
        vb = &it->second;
    else
        throw std::out_of_range("");

    vb->add_neighbor(*va);
    va->add_neighbor(*vb);
}


template <typename V>
V&
Graph<V>::
get_vertex(long name)
{
    return vertices.at(name);
}


template <typename V>
V&
Graph<V>::
get_some_vertex()
{
    for (auto& pair : vertices)
        return pair.second;
    throw std::out_of_range("graph is empty");
}


template <typename V>
const GraphVertexIterator<V>*
Graph<V>::
get_vertices()
{
    return __iter__();
}


template <typename V>
const GraphVertexIterator<V>*
Graph<V>::
__iter__()
{
    return new GraphVertexIterator<V>({ vertices.begin(), size() });
}

/*******************************************************************************
***************************** BASEGRAPH ****************************************
*******************************************************************************/


BaseGraph::
BaseGraph()
    : Graph<BaseVertex>()
{}


void
BaseGraph::
add_vertex(long name)
{
    BaseVertex v(name);
    this->vertices.insert(std::pair<long, BaseVertex>(name, v));
}


void
BaseGraph::
load_txt(char* path)
{
    std::ifstream file(path);
    int n;
    file >> n;

    for (int i=0; i<n; i++)
        this->add_vertex((long)i);

    int value;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
        {
            file >> value;
            if (value)
                vertices[i].add_neighbor(vertices[j]);
        }
}


ColoringGraph*
BaseGraph::
build_coloring_graph(int k)
{
    // TODO: make recursive backtracking based search
    ColoringGraph* cg = new ColoringGraph(k, this);
    for (long coloring=0; coloring<pow(k, size()); coloring++)
        if (is_valid_coloring(coloring, k))
            cg->add_vertex(coloring);
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
        BaseVertex v = pair.second;
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

// const struct GraphVertexIterator<ColoringVertex>*
// ColoringGraph::
// get_vertices()
// {
//     return __iter__();
// }
//
// const struct GraphVertexIterator<ColoringVertex>*
// ColoringGraph::
// __iter__()
// {
//     // struct GraphVertexIterator* ret;
//     return new struct GraphVertexIterator<ColoringVertex>({ vertices.begin(), size() });
//     // return ret;
// }


ColoringGraph::
ColoringGraph(int k, BaseGraph* bg)
    : colors(k), base(bg)
{}


void
ColoringGraph::
add_vertex(long name)
{
    ColoringVertex vertex(name, colors, this);
    vertices.insert(std::pair<long, ColoringVertex>(name, vertex));

    std::vector<long> v;
    for (int i=0; i<colors; v.push_back(i++*pow(colors, precompexp.size())));
    precompexp.push_back(v);
}


// ColoringVertex&
// ColoringGraph::
// get_vertex(long name)
// {
//     return (ColoringVertex) vertices.at(name);
// }
//
//
// ColoringVertex&
// ColoringGraph::
// get_some_vertex()
// {
//     for (auto& pair : vertices)
//             return pair.second;
// }


/*******************************************************************************
***************************** GraphVertexIterator*******************************
*******************************************************************************/


template <typename V>
V
GraphVertexIterator<V>::
next()
{
    if (this->len--)
        return this->it++->second;

    throw std::out_of_range("");
}


template <typename V>
V
GraphVertexIterator<V>::
__next__()
{
    return this->next();
}


template <typename V>
bool
GraphVertexIterator<V>::
hasnext()
{
    return (this->len > 0);
}


template <typename V>
GraphVertexIterator<V>*
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
