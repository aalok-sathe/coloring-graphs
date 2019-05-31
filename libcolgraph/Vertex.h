#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <map>
#include <set>
#include <list>
#include "Graph.h"

class Graph;

class Vertex
{
    friend class Graph;

    private:

    protected:
        std::set<long> neighbors;
        long name;
        int depth;
        int lowpoint;
        std::list<Vertex>::iterator parent;


    public:
        Vertex();
        Vertex(long name_);

        ~Vertex();

        long get_name();

        void add_neighbor(Vertex& other);

        Vertex* get_next_neighbor(Graph* g);

        int lp(Graph* g);

        bool check_for_cut();


};


class ColoringVertex : public Vertex
{
    private:

    protected:
        int nt;

    public:
};



#endif
