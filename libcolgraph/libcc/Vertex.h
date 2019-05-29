#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <map>
#include <unordered_set>



class Vertex
{
    friend class Graph;

    private:

    protected:
        std::unordered_set<long> neighbors;
        long name;
        int depth;
        int lowpoint;
        Vertex* parent;
        

    public:
        Vertex();
        Vertex(long name_);

        ~Vertex();

        long get_name();

        void add_neighbor(Vertex& other);

        Vertex get_next_neighbor();
};



class ColoringVertex : Vertex
{
    private:

    protected:
        int nt;

    public:
};



#endif
