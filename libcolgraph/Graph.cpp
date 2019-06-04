#ifndef __GRAPH_CPP__
#define __GRAPH_CPP__

#include "Graph.h"


Graph::
Graph() {}

Graph::
Graph(char* path)
{
    load_txt(path);
}

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
    vertices.insert(std::map<long, Vertex>::value_type(name, v));
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



const struct GraphVertexIterator*
Graph::
get_vertices()
{
    return __iter__();
}


const struct GraphVertexIterator*
Graph::
__iter__()
{
    // struct GraphVertexIterator* ret;
    return new struct GraphVertexIterator({ vertices.begin(), size() });
    // return ret;
}


BaseGraph::
BaseGraph(char* path)
{
    load_txt(path);
}



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

ColoringGraph::
ColoringGraph(int k, Graph* g)
    : colors(k), base(g)
{}


void
ColoringGraph::
add_vertex(long name)
{
    Graph::add_vertex(name);

    std::vector<long> v;
    for (int i=0; i<colors; v.push_back(i++*pow(colors, precompexp.size())));
    precompexp.push_back(v);
}


Vertex
GraphVertexIterator::
next()
{
    if (this->len--)
        return this->it++->second;

    throw std::out_of_range("");
}


Vertex
GraphVertexIterator::
__next__()
{
    return next();
}


bool
GraphVertexIterator::
hasnext()
{
    return (this->len > 0);
}


struct GraphVertexIterator*
GraphVertexIterator::
__iter__()
{
    return this;
}


#endif
