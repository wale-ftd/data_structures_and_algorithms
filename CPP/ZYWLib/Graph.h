#ifndef GRAPH_H
#define GRAPH_H

#include "SharedPointer.h"
#include "Array.h"


namespace DSaALib {

template <typename V, typename E>
class Graph: public Object
{
public:
    virtual V getVertex(s32 i) = 0;
    virtual bool getVertex(s32 i, V& value) = 0;
    virtual bool setVertex(s32 i, const V& value) = 0;
    virtual SharedPointer< Array<s32> > getAdjacent(s32 i) = 0;
    virtual E getEdge(s32 i, s32 j) = 0;
    virtual bool getEdge(s32 i, s32 j, E& value) = 0;
    virtual bool setEdge(s32 i, s32 j, const E& value) = 0;
    virtual bool removeEdge(s32 i, s32 j) = 0;
    virtual s32 vCount() = 0;
    virtual s32 eCount() = 0;
    virtual s32 OD(s32 i) = 0;
    virtual s32 ID(s32 i) = 0;

    virtual s32 TD(s32 i)
    {
        return OD(i) + ID(i);
    }
};

}


#endif // GRAPH_H
