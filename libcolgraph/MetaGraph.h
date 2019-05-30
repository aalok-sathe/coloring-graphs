#ifndef __METAGRAPH_H__
#define __METAGRAPH_H__

#include "MetaVertex.h"

class MetaGraph
{

    private:

    protected:
        std::list<MetaVertex> vertices;

    public:

        MetaGraph();
        ~MetaGraph();

        void add_vertex(MetaVertex m){};
    
};

#endif