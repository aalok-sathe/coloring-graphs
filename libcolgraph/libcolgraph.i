/* example.i */
%module libcolgraph

%include "exception.i"

%{
    #include <Python.h>
    #include <assert.h>
    #include "Graph.h"
    #include <iostream>
    #include "Vertex.h"
    #include <stdexcept>
%}

/* %except(python)
{
    try
    {
        $function
    }
    catch (...)
    {
        PyErr_SetString(PyExc_StopIteration, "end of iteration");
        return NULL;
    }
} */

%exception next
{
    try
    {
        $action
    }
    catch(...)
    {
        /* std::cout << 'NEXT EXCEPT 1' << std::endl; */
        PyErr_SetString(PyExc_StopIteration, "End of iterator");
        /* std::cout << 'NEXT EXCEPT 2' << std::endl; */
        SWIG_fail;
    }
}

%exception GraphVertexIterator::__next__
{
    try
    {
        /* std::cout << "$name $decl" << std::endl; */
        $action
    }
    catch(std::out_of_range& e)
    {
        PyErr_SetString(PyExc_StopIteration, "iterator exhausted");
        SWIG_fail;
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
