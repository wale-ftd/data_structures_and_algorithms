#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace DSaALib {

template <typename T>
class Array: public Object
{
protected:
    T *m_array;

public:
    virtual bool set(s32 i, const T& v)   /* O(1) */
    {
        bool ret = (0<=i) && (length()>i);
        if(ret)
        {
            m_array[i] = v;
        }

        return ret;
    }

    virtual bool get(s32 i, T& v) const   /* O(1) */
    {
        bool ret = (0<=i) && (length()>i);
        if(ret)
        {
            v = m_array[i];
        }

        return ret;
    }

    /* 重载数组访问操作符 */
    T& operator [](s32 i) /* O(1) */
    {
        bool ret = m_array && (0<=i) && (length()>i);
        if(ret)
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }
    T operator [](s32 i) const    /* O(1) */
    {
        /* 借助上面的[]实现 */
        return const_cast<Array<T>&>((*this))[i];
    }

    virtual s32 length() const = 0;
};

}

#endif // ARRAY_H
