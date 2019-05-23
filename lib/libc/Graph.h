#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <map>
#include <string>
#include "Vertex.h"

using namespace std;

/*
 *  the OG graph class
 */
class Graph
{
    private:

    protected:
        map<long, Vertex> vertices;

    public:

        Graph() {};

        ~Graph() {};

        void add_vertex(int name) {};

        void load_txt(char* path) {};

};


class BaseGraph : Graph
{
    private:

    protected:

    public:
};


class ColoringGraph
{
    private:
        Graph* base;

    protected:

    public:
};


#endif
