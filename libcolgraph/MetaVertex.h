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
    std::unordered_set<long> meta_neighbors;

public:

    MetaVertex();
    ~MetaVertex();

};

#endif