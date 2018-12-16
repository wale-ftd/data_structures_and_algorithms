#ifndef GRAPH_H
#define GRAPH_H

#include "SharedPointer.h"
#include "Array.h"


namespace DSaALib {

template <typename E>
struct Edge: public Object
{
    s32 b;  /* 起始顶点 */
    s32 e;  /* 邻接顶点 */
    E data; /* 权值 */

    Edge(s32 i = -1, s32 j = -1)
    {
        b = i;
        e = j;
    }

    Edge(s32 i, s32 j, const E& value)
    {
        b = i;
        e = j;
        data = value;
    }

    bool operator ==(const Edge<E>& obj)
    {
        return ((b==obj.b) && (e==obj.e));
    }

    bool operator !=(const Edge<E>& obj)
    {
        return (!(*this == obj));
    }
};

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
