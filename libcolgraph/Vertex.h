#ifndef __VERTEX_H__
#define __VERTEX_H__


#include <list>
#include "Graph.h"

class Graph;

class Vertex
{
    friend class Graph;

    public:
        
        long name;
        int depth;
        int lowpoint;
        std::list<Vertex>::iterator parent;

        Vertex();
        Vertex(long name_);

        ~Vertex();

        Vertex* get_next_neighbor(Graph* g);

        int lp(Graph* g);

        bool check_for_cut();


};


class BaseVertex : public Vertex
{
    public:
        std::list<long> neighbors;
        std:list<long>::iterator next_neighbor;
        void add_neighbor(Vertex& other);
}

class ColoringVertex : public Vertex
{
    public:
        int nt;
};



#endif
