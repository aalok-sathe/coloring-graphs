#ifndef __METAGRAPH_H__
#define __METAGRAPH_H__

#include "MetaVertex.h"

// forward declaration
template <typename V> class MetaVertex;


template <typename V>
class MetaGraph// : public Graph<MetaVertex>
{
    public:
        typename std::list<MetaVertex<V> > vertices;

        MetaGraph();
        ~MetaGraph();

        void add_vertex(MetaVertex<V> m);
        void remove_vertex(MetaVertex<V> m);

    	void save_txt();
};

#endif
