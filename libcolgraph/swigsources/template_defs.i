/* template_defs.i */


%import "GraphTemplates.h"

%template(GBVIt) GraphVertexIterator<BaseVertex>;
%template(GCVIt) GraphVertexIterator<ColoringVertex>;
%template(GMVIt) GraphVertexIterator<MetaVertex>;
%template(BVNIt) VertexNeighborIterator<BaseVertex>;
%template(CVNIt) VertexNeighborIterator<ColoringVertex>;
%template(MVNIt) VertexNeighborIterator<MetaVertex>;
%template(BGraph) Graph<BaseVertex>;
%template(CGraph) Graph<ColoringVertex>;
%template(MGraph) Graph<MetaVertex>;

%include "GraphTemplates.h"
%include "Graph.h"
%include "Vertex.h"
