#ifndef LISTGRAPH_H
#define LISTGRAPH_H


#include "Graph.h"
#include "DynamicArray.h"
#include "LinkList.h"

///* to debug */
//#include <iostream>
//using namespace std;

//#define WALE_ADD

namespace DSaALib {

template <typename V, typename E>
class ListGraph: public Graph<V, E>
{
protected:
    struct Vertex: public Object
    {
        V* data;                   /* 顶点数据元素值 */
        LinkList< Edge<E> > edge;  /* 邻接于该顶点的边 */

        Vertex()
        {
            data = NULL;
        }
    };
    LinkList<Vertex*> m_list;

public:
    ListGraph(u32 n = 0)
    {
        for(u32 i = 0; i < n; i++)
        {
            addVertex();
        }
    }

    /* 增加新的顶点， 返回顶点编号 */
    s32 addVertex()  /* O(n) */
    {
        s32 ret = -1;

        Vertex *nv = new Vertex();
        if(nv)
        {
            m_list.insert(nv);  /* 尾插 */

            ret = m_list.length() - 1;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new vertex object ...");
        }

        return ret;
    }

    /* 增加新顶点的同时附加数据元素 */
    s32 addVertex(const V& value)  /* O(n) */
    {
        s32 ret = addVertex();

        if(0 <= ret)
        {
            setVertex(ret, value);
        }

        return ret;
    }

    V getVertex(s32 i)  /* O(n) */
    {
        V ret;

        if(!getVertex(i, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    bool getVertex(s32 i, V& value)  /* O(n) */
    {
        bool ret = (0<=i) && (i<vCount());

        if(ret)
        {
            Vertex *v = m_list.get(i);
            if(v)
            {
                if(v->data)
                {
                    value = *(v->data);
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
                }
            }
        }

        return ret;
    }

    bool setVertex(s32 i, const V& value)  /* O(n) */
    {
        bool ret = (0<=i) && (i<vCount());

        if(ret)
        {
            Vertex *v = m_list.get(i);
            if(v)
            {
                V *d = v->data;
                if(d)
                {
                    *d = value;
                }
                else
                {
                    d = new V();
                    if(d)
                    {
                        *d = value;

                        v->data = d;
                    }
                    else
                    {
                        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new V object ...");
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    /* 删除最近增加的顶点 */
    void removeVertex()  /* O(n^2) */
    {
        if(0 < m_list.length())
        {
            s32 index = m_list.length() - 1;
            Vertex *v = m_list.get(index);

            /* 1. 将指针(指向待删除的顶点)节点从顶点链表中取出来，并释放这个节点在链表中所占的空间 */
            if(m_list.remove(index))
            {
                /* 2. 删除其它顶点指向待删除顶点的边 */
                for(s32 i = (m_list.move(0), 0); !m_list.end(); i++, m_list.next())
                {
                    s32 pos = m_list.current()->edge.find(Edge<E>(i, index));

                    if(0 <= pos)
                    {
                        m_list.current()->edge.remove(pos);
                    }
                }

//                /* todo: 奇怪！！！怎么不用删除 待删除顶点指向其它顶点的边呢？ */
//#ifdef WALE_ADD
//                s32 num_to_del = 0;
//                while(0 < v->edge.length())
//                {
//                    v->edge.remove(0);

//                    num_to_del++;
//                }
//                cout << "num_to_del = " << num_to_del << endl;
//#endif

                /* 3. 删除顶点保存的数据 */
                delete v->data;

                /* 4. 删除顶点 */
                delete v;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Vertex in current graph ...");
        }
    }

    SharedPointer< Array<s32> > getAdjacent(s32 i)  /* O(n) */
    {
        DynamicArray<s32> *ret = NULL;

        if((0<=i) && (i<vCount()))
        {
            Vertex *v = m_list.get(i);

#ifdef WALE_ADD
            if(0 < v->edge.length())
            {
#endif
                ret = new DynamicArray<s32>(v->edge.length());
                if(ret)
                {
                    for(s32 k = (v->edge.move(0), 0); !v->edge.end(); k++, v->edge.next())
                    {
                        ret->set(k, v->edge.current().e);
                    }
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object ...");
                }
#ifdef WALE_ADD
            }
#endif
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    E getEdge(s32 i, s32 j)  /* O(n) */
    {
        E ret;

        if(!getEdge(i, j, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Edge <i, j> is invalid ...");
        }

        return ret;
    }

    bool getEdge(s32 i, s32 j, E& value)  /* O(n) */
    {
        bool ret = (0<=i) && (i<vCount()) && (0<=j) && (j<vCount());

        if(ret)
        {
            Vertex *v = m_list.get(i);

#ifdef WALE_ADD
            s32 ctr = 0;

            for(ctr = 0, v->edge.move(0); !v->edge.end(); ctr++, v->edge.next())
            {
                if(v->edge.current().e == j)
                {
                    value = v->edge.current().data;

                    break;
                }
            }

            if(ctr == v->edge.length())
            {
                ret = false;
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
            }
#else
            s32 pos = v->edge.find(Edge<E>(i, j));

            if(0 <= pos)
            {
                value = v->edge.get(pos).data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
            }
#endif
        }

        return ret;
    }

    bool setEdge(s32 i, s32 j, const E& value)  /* O(n) */
    {
        bool ret = (0<=i) && (i<vCount()) && (0<=j) && (j<vCount());

        if(ret)
        {
            Vertex *v = m_list.get(i);

            s32 pos = v->edge.find(Edge<E>(i, j));

            if(0 <= pos)
            {
                ret = v->edge.set(pos, Edge<E>(i, j, value));
            }
            else
            {
                ret = v->edge.insert(0, Edge<E>(i, j, value));  /* 头插 */
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Edge <i, j> is invalid ...");
        }

        return ret;
    }

    bool removeEdge(s32 i, s32 j)  /* O(n) */
    {
        bool ret = (0<=i) && (i<vCount()) && (0<=j) && (j<vCount());

        if(ret)
        {
            Vertex *v = m_list.get(i);

            s32 pos = v->edge.find(Edge<E>(i, j));

            if(0 <= pos)
            {
                ret = v->edge.remove(pos);
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Edge <i, j> is invalid ...");
        }

        return ret;
    }

    s32 vCount()  /* O(1) */
    {
        return m_list.length();
    }

    s32 eCount()  /* O(n) */
    {
        s32 ret = 0;

        for(m_list.move(0); !m_list.end(); m_list.next())
        {
            ret += m_list.current()->edge.length();
        }

        return ret;
    }

    s32 OD(s32 i)  /* O(n) */
    {
        s32 ret = 0;

        if((0<=i) && (i<vCount()))
        {
            ret = m_list.get(i)->edge.length();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    s32 ID(s32 i)  /* O(n^2) */
    {
        s32 ret = 0;

        if((0<=i) && (i<vCount()))
        {
            Vertex *v = m_list.get(i);

            for(m_list.move(0); !m_list.end(); m_list.next())
            {
                Vertex *cv = m_list.current();

#ifdef WALE_ADD
                if(v != cv)
                {
#endif
                    LinkList< Edge<E> > &ll_e = cv->edge;

                    for(ll_e.move(0); !ll_e.end(); ll_e.next())
                    {
                        if(i == ll_e.current().e)
                        {
                            ret++;

                            break;
                        }
                    }
#ifdef WALE_ADD
                }
#endif
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    ~ListGraph()
    {
        while(0 < m_list.length())
        {
            Vertex *to_del = m_list.get(0);

            m_list.remove(0);

            delete to_del->data;

            delete to_del;
        }

    }
};

}


#endif // LISTGRAPH_H
