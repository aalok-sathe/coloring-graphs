#ifndef __VERTEX_H__
#define __VERTEX_H__


#include <list>
#include "Graph.h"

class Graph;

class Vertex
{

    public:
        
        long name;
        int depth;
        int lowpoint;
        std::list<Vertex>::iterator parent;

        Vertex();
        Vertex(long name_);

        ~Vertex();


        void add_neighbor(Vertex& v);
        void remove_neighbor(Vertex& v);

        long get_next_neighbor(Graph* g);

        int lp(Graph* g);

        bool check_for_cut();


};

class BaseVertex : public Vertex
{
    public:


        BaseVertex();
        BaseVertex(long name_);

        std::list<long> neighbors;
        std::list<long>::iterator next_neighbor;
        void add_neighbor(Vertex& v);
        void remove_neighbor(Vertex& other);
        long get_next_neighbor(Graph* g);
        
        int lp(Graph* g);

};

class ColoringVertex : public Vertex
{
    public:
        int nt;
        long get_next_neighbor(Graph* g);

        int lp(Graph* g);
};



#endif
