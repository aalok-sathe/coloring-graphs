/* template_defs.i */


%import "GraphTemplates.h"

%include "typemaps.i"
%include "std_vector.i"

%template(IntVector) std::vector<int>;
%template(LongVector) std::vector<long>;
%template(IntVectorVector) std::vector<std::vector<int> >;

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
