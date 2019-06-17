#ifndef __GRAPH_TEMPLATES_H__
#define __GRAPH_TEMPLATES_H__

#include <unordered_map>
#include <set>
#include <fstream>


// forward declarations
class Vertex;
class BaseVertex;
class ColoringVertex;
class MetaVertex;
template <typename V> class Graph;
class BaseGraph;
class ColoringGraph;
class MetaGraph;


// a base iterator class to support iteration over a Vertex's
// neighboring vertices. Assumes an instance of polymorphic Vertex.
// may be subclassed to specialize for particular kinds of vertices.
template <typename V>
class VertexNeighborIterator
{
    public:
        VertexNeighborIterator() {};
        virtual ~VertexNeighborIterator() {};

        virtual long next() = 0;
        virtual long __next__();

        virtual bool hasnext() = 0;

        virtual VertexNeighborIterator<V>* __iter__();
};


// a base iterator class to support iteration over a Graph<>'s
// vertices. Assumes an instance of polymorphic Graph class,
// and assumes that vertices are stored in an internal hashmap
// mapping long->Vertex-inherited objects
// may be subclassed to specialize for particular kinds of vertices.
template <typename V>
class GraphVertexIterator
{
    public:
        typename std::unordered_map<long, V*>::iterator it;
        long len;

        GraphVertexIterator<V>() {};
        GraphVertexIterator<V>(typename std::unordered_map<long, V*>::iterator it_,
                               long len_)
            : it(it_), len(len_) {};
        virtual ~GraphVertexIterator() {};

        virtual V next();
        virtual V __next__();

        virtual bool hasnext();

        virtual GraphVertexIterator<V>* __iter__();
};


// the OG Graph<> class. It is a pure virtual class so it cannot
// be instantiated. Some of the methods may need implementation
// depending on the purpose of the graph being subclassed, in
// order for the class to function.
// Maintains a hashmap of <long, Vertex*>, so each vertex must have
// a unique long-type name.
// Stores V objects which are instances of or subclassed from Vertex
// Supports iteration via GraphVertexIterator objects, making it
// easy to wrap the iterator as a standalone object in high-level
// languages such as Python
template <typename V>
class Graph
{
    public:
        std::unordered_map<long, V*> vertices;

        Graph();
        virtual ~Graph();

        // load in data from a standard adjacency matrix format
        // text file
        virtual void load_txt(char* path) {};

        // TODO
        virtual void save_txt() {};

        // returns the size of the graph in terms of the number of vertices
        virtual long size();
        // proxy method that just calls this->size()
        // virtual long __len__() { return size(); };

        virtual void add_vertex(long name) = 0;

        virtual V& get_vertex(long name);
        virtual V& get_some_vertex();

        virtual const GraphVertexIterator<V>* __iter__() = 0;
        virtual const GraphVertexIterator<V>* get_vertices() = 0;

        virtual MetaGraph* tarjans();

};



#endif
