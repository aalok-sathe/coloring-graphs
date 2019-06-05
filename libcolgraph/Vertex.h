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

<<<<<<< HEAD
        void add_neighbor(Vertex& other);

        long get_next_neighbor(Graph* g);
=======
        
        std::list<long>::iterator next_neighbor;

        Vertex* get_next_neighbor(Graph* g);
>>>>>>> b17108357b0899ed1393deceda9536e5ec8e7878

        int lp(Graph* g);

        bool check_for_cut();


};

class BaseVertex : public Vertex
{
    public:
<<<<<<< HEAD

        BaseVertex();
        BaseVertex(long name_);

        std::list<long> neighbors;
        std::list<long>::iterator next_neighbor;
        void add_neighbor(Vertex& other);
        long get_next_neighbor(Graph* g);

};
=======
     std::list<long> neighbors;
     void add_neighbor(Vertex& other);
};

>>>>>>> b17108357b0899ed1393deceda9536e5ec8e7878

class ColoringVertex : public Vertex
{
    public:
        int nt;
<<<<<<< HEAD
        long get_next_neighbor(Graph* g);
=======

        Vertex* get_next_neighbor(Graph* g);
>>>>>>> b17108357b0899ed1393deceda9536e5ec8e7878
};



#endif
