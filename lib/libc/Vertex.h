#ifndef __VERTEX_H__
#define __VERTEX_H__


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

    public:

        Vertex() {};

        ~Vertex() {};
};


class ColoringVertex : Vertex
{
    private:

    protected:

    public:
};

#endif
