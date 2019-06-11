#ifndef __METAVERTEX_CPP__
#define __METAVERTEX_CPP__

#include "MetaVertex.h"

template <typename V>
MetaVertex<V>::
MetaVertex()
{}


template <typename V>
MetaVertex<V>::
MetaVertex(V& v)
{
	this->name = v.name;
	this->depth = v.depth;
	vertices.push_back(v);
}


template <typename V>
MetaVertex<V>::
~MetaVertex()
{}


template <typename V>
void
MetaVertex<V>::
connect(MetaVertex<V> v)
{
	this->meta_neighbors.push_back(v);
	v.meta_neighbors.push_back(*this);
}

template <typename V>
void
MetaVertex<V>::
disconnect(MetaVertex<V> v)
{
	this->meta_neighbors.remove(v);
	v.meta_neighbors.remove(*this);
}




#endif
