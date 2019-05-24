#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <unordered_set>

using namespace std;

enum V_ATTR
{
    NAME,
    COLOR
};


class Vertex
{
    friend class Graph;

    private:

    protected:
        long name;
        unordered_set<long> neighbors;

    public:
        Vertex();
        Vertex(long name_);

        ~Vertex();

        long get_name();

        void add_neighbor(Vertex& other);

        unordered_set<long>::iterator get_neighbors();
};


class ColoringVertex : Vertex
{
    private:

    protected:

    public:
};

#endif
