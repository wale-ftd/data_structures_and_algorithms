#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Standard.h"
#include "Array.h"

namespace DSaALib {

template <typename T, int N>
class StaticArray: public Array<T>
{
protected:
    T m_space[N];

public:
    StaticArray()   /* O(1) */
    {
        this->m_array = m_space;
    }

    /* 拷贝构造和赋值操作 */
    StaticArray(const StaticArray<T, N>& obj)   /* O(n) */
    {
        this->m_array = m_space;

        for(s32 i = 0; N > i; i++)
        {
            m_space[i] = obj.m_space[i];
        }
    }
    StaticArray<T, N>& operator =(const StaticArray<T, N>& obj) /* O(n) */
    {
        if(this != &obj)
        {
            for(s32 i = 0; N > i; i++)
            {
                m_space[i] = obj.m_space[i];
            }
        }

        return *this;
    }

    s32 length() const    /* O(1) */
    {
        return N;
    }
};

}

#endif // STATICARRAY_H
