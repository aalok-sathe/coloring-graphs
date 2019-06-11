#ifndef __METAGRAPH_CPP__
#define __METAGRAPH_CPP__

#include "MetaGraph.h"
#include <list>
#include <fstream>


template <typename V>
MetaGraph<V>::
MetaGraph()
{}


template <typename V>
MetaGraph<V>::
~MetaGraph()
{}


template <typename V>
void
MetaGraph<V>::
add_vertex(MetaVertex<V> m)
{
	vertices.push_back(m);
}


template <typename V>
void
MetaGraph<V>::
remove_vertex(MetaVertex<V> m)
{
	for (auto& n : m.meta_neighbors)
	{
		m.disconnect(n);
	}

	vertices.remove(m);
}


#endif
