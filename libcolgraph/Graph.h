#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <cstddef>
// #include <string>
#include <fstream>
#include "Vertex.h"



struct GraphVertexIterator
{
    std::map<long, Vertex>::iterator it;
    long len;
    int stop_iter;

    ~GraphVertexIterator() {};

    Vertex __next__()
    {
        if (this->len--)
            return (*this->it++).second;

        throw std::out_of_range("");
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

        struct GraphVertexIterator __iter__();
        struct GraphVertexIterator get_vertices();

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
