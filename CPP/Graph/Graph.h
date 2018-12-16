#ifndef GRAPH_H
#define GRAPH_H

#include "SharedPointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"

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

    SharedPointer< Array<s32> > BFS(s32 i)
    {
        DynamicArray<s32> *ret = NULL;

        if((0<=i) && (i<vCount()))
        {
            LinkQueue<s32> q;
            LinkQueue<s32> r;
            DynamicArray<bool> visited(vCount());

            for(s32 j = 0; j < visited.length(); j++)
            {
                visited[j] = false;
            }

            q.add(i);

            while(0 < q.length())
            {
                s32 v = q.front();

                q.remove();

                if(!visited[v])
                {
                    SharedPointer< Array<s32> > adj = getAdjacent(v);

                    for(s32 j = 0; j < adj->length(); j++)
                    {
                        q.add((*adj)[j]);
                    }

                    r.add(v);

                    visited[v] = true;
                }
            }

            ret = LinkQueue2Array(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    SharedPointer< Array<s32> > DFS(s32 i)
    {
        DynamicArray<s32> *ret = NULL;

        if((0<=i) && (i<vCount()))
        {
            LinkStack<s32> s;
            LinkQueue<s32> r;
            DynamicArray<bool> visited(vCount());

            for(s32 j = 0; j < visited.length(); j++)
            {
                visited[j] = false;
            }

            s.push(i);

            while(0 < s.size())
            {
                s32 v = s.top();

                s.pop();

                if(!visited[v])
                {
                    SharedPointer< Array<s32> > adj = getAdjacent(v);

#if 0
                    for(s32 j = 0; j < adj->length(); j++)
#else
                    for(s32 j = adj->length()-1; j >= 0; j--)
#endif
                    {
                        s.push((*adj)[j]);
                    }

                    r.add(v);

                    visited[v] = true;
                }
            }

            ret = LinkQueue2Array(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

protected:
    template<typename T>
    DynamicArray<T>* LinkQueue2Array(LinkQueue<T>& lq)
    {
        DynamicArray<T> *ret = new DynamicArray<T>(lq.length());

        if(ret)
        {
            for(s32 i = 0; i < ret->length(); i++, lq.remove())
            {
                ret->set(i, lq.front());
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object ...");
        }

        return ret;
    }
};

}


#endif // GRAPH_H
