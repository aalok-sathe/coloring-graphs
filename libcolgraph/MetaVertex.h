#ifndef __METAVERTEX_H__
#define __METAVERTEX_H__
#include "Vertex.h"

class Vertex;

class MetaVertex
{
    friend class MetaGraph;
    friend class Graph;
  

public:

    long name;
    std::list<Vertex> vertices;
    std::list<MetaVertex> meta_neighbors;
    int depth;

    MetaVertex();

    MetaVertex(Vertex v);

    ~MetaVertex();

    // add to each other's neighbor list
    static void connect(MetaVertex v1, MetaVertex v2);



};

#endif