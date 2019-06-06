#ifndef __METAVERTEX_CPP__
#define __METAVERTEX_CPP__

#include "MetaVertex.h"

MetaVertex::
MetaVertex() {}

MetaVertex::
MetaVertex(Vertex v)
{
	this.name = v.name;
	this.depth = v.depth;
	vertices.push_back(v);
}

MetaVertex::
~MetaVertex(){}

static void
MetaVertex::
connect(MetaVertex v1, MetaVertex v2)
{
	v1.meta_neighbors.push_back(v2);
	v2.meta_neighbors.push_back(v1);
}

static void
MetaVertex::
disconnect(MetaVertex v1, MetaVertex v2)
{
	v1.meta_neighbors.remove(v2);
	v2.meta_neighbors.remove(v1);
}



#endif