#ifndef __METAVERTEX_H__
#define __METAVERTEX_H__
#include "Vertex.h"

class Vertex;

class MetaVertex
{

  

public:

    long name;
    std::list<Vertex> vertices;
    std::list<MetaVertex> meta_neighbors;
    int depth;

    MetaVertex();

    MetaVertex(Vertex v);

    ~MetaVertex();

    // add to each other's neighbor list
    void connect(MetaVertex v);
    void disconnect(MetaVertex v);

    bool operator==(const MetaVertex v) const
    {
        return this->name == v.name;
    }


};

#endif