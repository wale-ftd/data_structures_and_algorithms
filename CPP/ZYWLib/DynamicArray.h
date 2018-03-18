#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Standard.h"
#include "Array.h"

namespace DSaALib {

template <typename T>
class DynamicArray: public Array<T>
{
protected:
    s32 m_length;

    T* copy(T *array, s32 a_len, s32 new_len)   // O(min(a_len, new_len)) ==> O(n)
    {
        T *ret = NULL;

        if(array && (0<a_len) && (0<new_len))
        {
            T *na = new T[new_len];
            if(na)
            {
                s32 len = (a_len<new_len) ? a_len : new_len;

                for(s32 i = 0; i < len; i++)
                {
                    na[i] = array[i];
                }

                ret = na;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter is invalid ...");
        }

        return ret;
    }

    void update(T *array, s32 a_len)  // O(1)
    {
        if(array && (0<a_len))
        {
            T *a_tmp = this->m_array;

            this->m_array = array;
            m_length = a_len;

            if(a_tmp)
            {
                delete [] a_tmp;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter is invalid ...");
        }
    }

    void init(T *array, s32 a_len)    // O(1)
    {
        if(array && (0<a_len))
        {
            this->m_array = array;
            m_length = a_len;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter is invalid ...");
        }
    }

public:
    DynamicArray(s32 length = 1)  // O(1)
    {
        if(0 < length)
        {
#if 1
            init(new T[length], length);
#else
            this->m_array = new T[length];
            if(this->m_array)
            {
                m_length = length;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object ...");
            }
#endif
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter length is invalid ...");
        }
    }

    DynamicArray(const DynamicArray<T>& obj)    // O(n)
    {
#if 1
        init(copy(obj.m_array, obj.length(), obj.length()), obj.length());
#else
        this->m_array = new T[obj.length()];
        if(this->m_array)
        {
            m_length = obj.length();

            for(s32 i = 0; i < m_length; i++)
            {
                this->m_array[i] = obj.m_array[i];
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to copy DynamicArray object ...");
        }
#endif
    }

    DynamicArray<T>& operator =(const DynamicArray<T>& obj) // O(n)
    {
        if(&obj != this)
        {
#if 1
            update(copy(obj.m_array, obj.length(), obj.length()), obj.length());
#else
            T *da = new T[obj.length()];
            if(da)
            {
                for(s32 i = 0; i < obj.length(); i++)
                {
                    da[i] = obj.m_array[i];
                }

                T *da_tmp = this->m_array;

                this->m_array = da;
                m_length = obj.length();

                if(da_tmp)
                {
                    delete [] da_tmp;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to assign DynamicArray object ...");
            }
#endif
        }

        return *this;
    }

    void resize(s32 length)   /* 动态重置数组的长度 */ // O(n)
    {
        if(length != m_length)
        {
#if 1
            update(copy(this->m_array, m_length, length), length);
#else
            T *da = new T[length];
            if(da)
            {
                s32 len = (m_length<=length) ? m_length : length;

                for(s32 i = 0; i < len; i++)
                {
                    da[i] = this->m_array[i];
                }

                T *da_tmp = this->m_array;

                this->m_array = da;
                m_length = length;

                if(da_tmp)
                {
                    delete [] da_tmp;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynamicArray object ...");
            }
#endif
        }
    }

    s32 length() const    /* O(1) */
    {
        return m_length;
    }

    ~DynamicArray()  /* 归还空间 */ // O(1)
    {
        if(this->m_array)
        {
            delete [] this->m_array;

            this->m_array = NULL;
        }
    }
};

}

#endif // DYNAMICARRAY_H
