#ifndef __METAVERTEX_H__
#define __METAVERTEX_H__
#include "Vertex.h"
// #include <map>
// #include <unordered_set>

class MetaVertex
{
    friend class MetaGraph;

private:

protected:
    long name;
    std::map<long, Vertex> base_vertices;
    std::unordered_set<long> meta_neighbors;

public:

    MetaVertex();
    ~MetaVertex();

};

#endif