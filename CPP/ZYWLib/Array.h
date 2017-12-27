#ifndef ARRAY_H
#define ARRAY_H

#include "Standard.h"
#include "Object.h"
#include "Exception.h"

NAMESPACE_DEF_START(ZYWLib)

template <typename T>
class Array: public Object
{
protected:
    T *m_array;

public:
    virtual ZYW_BOOL set(ZYW_INT32 i, const T& v)   /* O(1) */
    {
        ZYW_BOOL ret = (0<=i) && (length()>i);
        if(ret)
        {
            m_array[i] = v;
        }

        return ret;
    }

    virtual ZYW_BOOL get(ZYW_INT32 i, T& v) const   /* O(1) */
    {
        ZYW_BOOL ret = (0<=i) && (length()>i);
        if(ret)
        {
            v = m_array[i];
        }

        return ret;
    }

    /* 重载数组访问操作符 */
    T& operator [](ZYW_INT32 i) /* O(1) */
    {
        ZYW_BOOL ret = m_array && (0<=i) && (length()>i);
        if(ret)
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }
    T operator [](ZYW_INT32 i) const    /* O(1) */
    {
        /* 借助上面的[]实现 */
        return const_cast<Array<T>&>((*this))[i];
    }

    virtual ZYW_INT32 length() const = 0;
};

NAMESPACE_DEF_END

#endif // ARRAY_H
