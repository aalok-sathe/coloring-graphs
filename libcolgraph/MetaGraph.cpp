#ifndef __METAGRAPH_CPP__
#define __METAGRAPH_CPP__

#include "MetaGraph.h"
#include <list>
#include <fstream>

using namespace std;

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

void
MetaGraph::
remove_vertex(MetaVertex m)
{
	for (auto& n : m.meta_neighbors)
	{
		m.disconnect(n);
	}
	
	vertices.remove(m);
}


// void
// MetaGraph::
// save_txt()
// {
// 	ofstream outfile;
// 	outfile.open("graph.txt", ios::out);

// 	for (auto& metavertex : vertices)
// 	{
// 		for (auto& metavertex : vertices)
// 		{
// 			if 
// 		}
// 	outfile << endl;
// 	}
// }

#endif