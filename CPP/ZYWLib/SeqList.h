#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace ZYWLib {

template <typename T>
class SeqList: public List<T>
{
protected:
    T* m_array;             /* ָ��˳��洢�ռ� */
    ZYW_INT32 m_length;     /* ��ǰ���Ա��� */

public:
    ZYW_BOOL insert(ZYW_INT32 i, const T& e)
    {
        ZYW_BOOL ret = m_array && (0<=i) && (m_length>=i) && (capacity()>m_length);

        if(ret)
        {
            for(ZYW_INT32 cur = m_length-1; cur >= i; cur--)
            {
                m_array[cur+1] = m_array[cur];
            }

            m_array[i] = e;

            m_length++;
        }

        return ret;
    }

    ZYW_BOOL insert(const T& e)
    {
        return insert(m_length, e);
    }

    ZYW_BOOL remove(ZYW_INT32 i)
    {
        ZYW_BOOL ret = m_array && (0<=i) && (m_length>i);

        if(ret)
        {
            for(ZYW_INT32 cur = i; cur < (m_length-1); cur++)
            {
                m_array[cur] = m_array[cur+1];

            }

            m_length--;
        }

        return ret;
    }

    ZYW_BOOL set(ZYW_INT32 i, const T& e)
    {
        ZYW_BOOL ret = m_array && (0<=i) && (m_length>i);

        if(ret)
        {
            m_array[i] = e;
        }

        return ret;
    }

    ZYW_BOOL get(ZYW_INT32 i, T& e) const
    {
        ZYW_BOOL ret = m_array && (0<=i) && (m_length>i);

        if(ret)
        {
            e = m_array[i];
        }

        return ret;
    }

    ZYW_INT32 find(const T& e) const    // O(n)
    {
        ZYW_INT32 ret = -1;

        for(ZYW_INT32 i = 0; i < length(); i++)
        {
            if(m_array[i] == e)
            {
                ret = i;

                break;
            }
        }

        return ret;
    }

    ZYW_INT32 length() const
    {
        return m_length;
    }

    void clear()
    {
        m_length = 0;
    }

    /* ˳��洢���Ա��������ʷ�ʽ */
    T& operator [](ZYW_INT32 i)
    {
        ZYW_BOOL ret = m_array && (0<=i) && (m_length>i);

        if(ret)
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }

    T operator [](ZYW_INT32 i) const
    {
#if 1
        /* ���������[]ʵ�� */
        return (const_cast<SeqList<T>&>(*this))[i];
#else
        ZYW_BOOL ret = m_array && (0<=i) && (m_length>i);

        if(ret)
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
#endif
    }

    /* ˳��洢�ռ������ */
    virtual ZYW_INT32 capacity() const = 0;
};

}

#endif // SEQLIST_H
