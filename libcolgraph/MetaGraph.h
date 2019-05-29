#ifndef __METAGRAPH_H__
#define __METAGRAPH_H__

#include "MetaVertex.h"

class MetaGraph
{

    private:

    protected:
        std::map<long, MetaVertex> vertices;

    public:

        MetaGraph();
        ~MetaGraph();
    
};

#endif