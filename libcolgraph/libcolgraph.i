/* libcolgraph.i */

%module libcolgraph

%include "exception.i"

%include "swigsrc/wrapped_exceptions.i"
%include "swigsrc/pyoverrides.i"
%include "swigsrc/cpp_inline.i"
%include "swigsrc/template_defs.i"

%include "GraphTemplates.h"
%include "Graph.h"
%include "Vertex.h"
