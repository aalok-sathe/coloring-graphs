#ifndef __METAVERTEX_CPP__
#define __METAVERTEX_CPP__

#include "MetaVertex.h"

MetaVertex::
MetaVertex() {}

MetaVertex::
MetaVertex(Vertex v)
{
	this->name = v.name;
	this->depth = v.depth;
	vertices.push_back(v);
}

MetaVertex::
~MetaVertex(){}

void
MetaVertex::
connect(MetaVertex v)
{
	this->meta_neighbors.push_back(v);
	v.meta_neighbors.push_back(*this);
}

void
MetaVertex::
disconnect(MetaVertex v)
{
	this->meta_neighbors.remove(v);
	v.meta_neighbors.remove(*this);
}




#endif