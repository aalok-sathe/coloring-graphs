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


%exception GraphVertexIterator::__next__
{
    try
    {
        $action
    }
    catch(std::out_of_range& e)
    {
        PyErr_SetString(PyExc_StopIteration, "end of iterator reached");
        SWIG_fail;
    }
}
%exception VertexNeighborIterator::__next__
{
    try
    {
        $action
    }
    catch(std::out_of_range& e)
    {
        PyErr_SetString(PyExc_StopIteration, "end of iterator reached");
        SWIG_fail;
    }
}
%exception ColoringVertexNeighborIterator::__next__
{
    try
    {
        $action
    }
    catch(std::out_of_range& e)
    {
        PyErr_SetString(PyExc_StopIteration, "end of iterator reached");
        SWIG_fail;
    }
}
%exception BaseGraph::get_vertex
{
    try
    {
        $action
    }
    catch(std::out_of_range& e)
    {
        PyErr_SetString(PyExc_KeyError, "queried key not found in lookup");
        SWIG_fail;
    }
}
%exception ColoringGraph::get_vertex
{
    try
    {
        $action
    }
    catch(std::out_of_range& e)
    {
        PyErr_SetString(PyExc_KeyError, "queried key not found in lookup");
        SWIG_fail;
    }
}

/* %template(BaseGraph) BaseGraph<Vertex>;
%template(ColoringGraph) ColoringGraph<ColoringVertex>; */

/* %pythonprepend GraphVertexIterator::GraphVertexIterator %{
    print('thisown was: %d' % self.thisown)
%} */

%include "Graph.h"
%include "Vertex.h"

/* %template(Graph) Graph<Vertex>; */
