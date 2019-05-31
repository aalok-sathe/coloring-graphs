#ifndef __METAVERTEX_CPP__
#define __METAVERTEX_CPP__

#include "MetaVertex.h"

MetaVertex::
MetaVertex() {}

MetaVertex::
MetaVertex(Vertex v)
{
	vertices.push_back(v);
}

MetaVertex::
~MetaVertex(){}

static void
MetaVertex::
connect(MetaVertex v1, MetaVertex v2)
{
	v1.meta_neighbors.insert(v2);
	v2.meta_neighbors.insert(v1);
}

#endif