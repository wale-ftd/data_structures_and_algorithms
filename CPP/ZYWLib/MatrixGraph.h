#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "DynamicArray.h"


namespace DSaALib {

template <s32 N, typename V, typename E>
class MatrixGraph: public Graph<V, E>
{
protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    s32 m_eCount;

public:
    MatrixGraph()
    {
        for(s32 i = 0; i < vCount(); i++)
        {
            m_vertexes[i] = NULL;

            for(s32 j = 0; j < vCount(); j++)
            {
                m_edges[i][j] = NULL;
            }
        }

        m_eCount = 0;
    }

    V getVertex(s32 i)
    {
        V ret;

        if(!getVertex(i, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    bool getVertex(s32 i, V& value)
    {
        bool ret = (0<=i) && (i<vCount());

        if(ret)
        {
            if(m_vertexes[i])
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
            }
        }

        return ret;
    }

    bool setVertex(s32 i, const V& value)
    {
        bool ret = (0<=i) && (i<vCount());

        if(ret)
        {
            V *vertex = m_vertexes[i];

            if(!vertex)
            {
                vertex = new V();

                if(vertex)
                {
                    *vertex = value;

                    m_vertexes[i] = vertex;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new vertex value ...");
                }
            }
            else
            {
                *vertex = value;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    SharedPointer< Array<s32> > getAdjacent(s32 i)
    {
        DynamicArray<s32> *ret = NULL;

        if((0<=i) && (i<vCount()))
        {
            s32 adj_ver_ctr = 0;

            for(s32 j = 0; j < vCount(); j++)
            {
                if(m_edges[i][j])
                {
                    adj_ver_ctr++;
                }
            }

            ret = new DynamicArray<s32>(adj_ver_ctr);
            if(ret)
            {
                adj_ver_ctr = 0;

                for(s32 j = 0; j < vCount(); j++)
                {
                    if(m_edges[i][j])
                    {
                        ret->set(adj_ver_ctr++, j);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    E getEdge(s32 i, s32 j)
    {
        E ret;

        if(!getEdge(i, j, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Index <i, j> is invalid ...");
        }

        return ret;
    }

    bool getEdge(s32 i, s32 j, E& value)
    {
        bool ret = (0<=i) && (i<vCount()) && (0<=j) && (j<vCount());

        if(ret)
        {
            if(m_edges[i][j])
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
            }
        }

        return ret;
    }

    bool setEdge(s32 i, s32 j, const E& value)
    {
        bool ret = (0<=i) && (i<vCount()) && (0<=j) && (j<vCount());

        if(ret)
        {
            E *edge = m_edges[i][j];

            if(!edge)
            {
                edge = new E();

                if(edge)
                {
                    *edge = value;

                    m_edges[i][j] = edge;
                    m_eCount++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new vertex value ...");
                }
            }
            else
            {
                *edge = value;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index <i, j> is invalid ...");
        }

        return ret;
    }

    bool removeEdge(s32 i, s32 j)
    {
        bool ret = (0<=i) && (i<vCount()) && (0<=j) && (j<vCount());

        if(ret)
        {
            if(m_edges[i][j])
            {
                E* toDel = m_edges[i][j];

                m_edges[i][j] = NULL;
                m_eCount--;

                delete toDel;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index <i, j> is invalid ...");
        }

        return ret;
    }

    s32 vCount()
    {
        return N;
    }

    s32 eCount()
    {
        return m_eCount;
    }

    s32 OD(s32 i)
    {
        s32 ret = 0;

        if((0<=i) && (i<vCount()))
        {
            for(s32 j = 0; j < vCount(); j++)
            {
                if(m_edges[i][j])
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    s32 ID(s32 i)
    {
        s32 ret = 0;

        if((0<=i) && (i<vCount()))
        {
            for(s32 j = 0; j < vCount(); j++)
            {
                if(m_edges[j][i])
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    ~MatrixGraph()
    {
        for(s32 i = 0; i < vCount(); i++)
        {
            for(s32 j = 0; j < vCount(); j++)
            {
                delete m_edges[i][j];
            }

            delete m_vertexes[i];
        }
    }
};

}


#endif // MATRIXGRAPH_H
