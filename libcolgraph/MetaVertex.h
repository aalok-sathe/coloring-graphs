#ifndef __METAVERTEX_H__
#define __METAVERTEX_H__
#include "Vertex.h"

class Vertex;

class MetaVertex
{
    friend class MetaGraph;
    friend class Graph;

private:

protected:
    long name;
    std::list<Vertex> vertices;
    std::unordered_set<MetaVertex> meta_neighbors;

public:

    MetaVertex();
    ~MetaVertex();

    // // adds v to neighbor list
    // void add_neighbor(MetaVertex v);

    // // add to each other's neighbor list
    // void connect(MetaVertex v);

};

#endif