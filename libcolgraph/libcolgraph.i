/* example.i */
%module libcolgraph

%include "exception.i"

%{
    #include <assert.h>
    #include "Graph.h"
    #include "Vertex.h"
    #include <stdexcept>
%}

%exception GraphVertexIterator::next
{
    try
    {
        $action
    }
    catch(1)
    {
        PyErr_SetString(PyExc_StopIteration, "End of iterator");
        return NULL;
    }
}

%exception Graph::get_vertex
{
    try
    {
        $action
    }
    catch(std::out_of_range)
    {
        PyErr_SetString(PyExc_KeyError, "Key not found");
        return NULL;
    }
}


/*%inline %{
  struct GraphVertexIterator {
    std::map<long, Vertex>::iterator it;
    long len;
    ~GraphVertexIterator() {};
  };
%}*/

%include "Graph.h"
%include "Vertex.h"

/*%extend GraphVertexIterator {
  struct GraphVertexIterator* __iter__() {
    return $self;
  }

  Vertex __next__() {
    if ($self->len--) {
      return (*$self->it++).second;
    }
    stop_iter = 1;
    return 0;
  }
}*/

/*%extend Graph {
  struct GraphVertexIterator get_vertices() {
    return $self->__iter__();
  }

}*/
