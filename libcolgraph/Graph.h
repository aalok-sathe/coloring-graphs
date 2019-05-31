#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <cstddef>
#include <stdexcept>
// #include <string>
#include <fstream>
#include "Vertex.h"



struct GraphVertexIterator
{
    std::map<long, Vertex>::iterator it;
    long len;

    ~GraphVertexIterator() {};

    Vertex next()
    {
        if (this->len-- > 0)
            return this->it++->second;

        throw std::out_of_range("");
    }
    Vertex __next__()
    {
        return next();
    }

    struct GraphVertexIterator* __iter__()
    {
        return this;
    }
};

/*
 *  the OG graph class
 */
class Graph
{
    public:
        std::map<long, Vertex> vertices;

        Graph();
        ~Graph();

        void load_txt(char* path);

        long size();
        long __len__() { return size(); };

        void add_vertex(long name);

        Vertex& get_vertex(long name);

        const struct GraphVertexIterator* __iter__();
        const struct GraphVertexIterator* get_vertices();

};


class BaseGraph : public Graph
{
    public:

};


class ColoringGraph : public Graph
{
    public:
        Graph* base;


};


#endif
