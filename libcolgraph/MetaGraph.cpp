#ifndef __METAGRAPH_CPP__
#define __METAGRAPH_CPP__

#include "MetaGraph.h"
#include <list>

MetaGraph::MetaGraph()
{

}

MetaGraph::~MetaGraph()
{

}

void
MetaGraph::
add_vertex(MetaVertex m)
{
	vertices.push_back(m);
}

#endif