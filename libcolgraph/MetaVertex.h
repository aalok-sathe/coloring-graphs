#ifndef __METAVERTEX_H__
#define __METAVERTEX_H__

#include <list>
#include "Vertex.h"


class Vertex;


template <typename V>
class MetaVertex
{

    public:

        long name;
        typename std::list<V> vertices;
        typename std::list<MetaVertex<V> > meta_neighbors;
        int depth;

        MetaVertex();
        MetaVertex(V& v);

        ~MetaVertex();

        // add to each other's neighbor list
        void connect(MetaVertex<V> v);
        void disconnect(MetaVertex<V> v);

        bool operator==(const MetaVertex<V> v) const
        {
            return this->name == v.name;
        }

};

#endif
