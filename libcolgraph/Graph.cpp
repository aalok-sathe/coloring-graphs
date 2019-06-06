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
    this->vertices.insert(std::pair<long, Vertex>(name, v));
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


const struct GraphVertexIterator<Vertex>*
Graph::
get_vertices()
{
    return __iter__();
}


const struct GraphVertexIterator<Vertex>*
Graph::
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


ColoringGraph*
BaseGraph::
build_coloring_graph(int k)
{
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
ColoringGraph(int k, Graph* g)
    : colors(k), base(g)
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


template <typename V, typename V_iter>
V
GraphVertexIterator<V, V_iter>::
next()
{
    if (this->len--)
        return (V) this->it++->second;

    throw std::out_of_range("");
}


template <typename V, typename V_iter>
V
GraphVertexIterator<V, V_iter>::
__next__()
{
    return (V) next();
}


template <typename V, typename V_iter>
bool
GraphVertexIterator<V, V_iter>::
hasnext()
{
    return (this->len > 0);
}


template <typename V, typename V_iter>
struct GraphVertexIterator<V, V_iter>*
GraphVertexIterator<V, V_iter>::
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
