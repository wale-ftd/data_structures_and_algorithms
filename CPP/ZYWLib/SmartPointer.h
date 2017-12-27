#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Object.h"

namespace ZYWLib
{
template <typename T>
class SmartPointer: public Object
{
protected:
    T* m_pointer;

public:
    SmartPointer(T* p = NULL)
    {
        m_pointer = p;
    }

    SmartPointer(const SmartPointer<T>& sp)
    {
        if(m_pointer)
        {
            delete m_pointer;
            m_pointer = NULL;
        }

        m_pointer = sp.m_pointer;
        const_cast<SmartPointer<T>&>(sp).m_pointer = NULL;
    }

    T* operator ->()
    {
        return m_pointer;
    }

    T& operator *()
    {
        return *m_pointer;
    }

    SmartPointer<T>& operator =(const SmartPointer<T>& sp)
    {
        if(this != &sp)
        {
            if(m_pointer)
            {
                delete m_pointer;
                m_pointer = NULL;
            }

            m_pointer = sp.m_pointer;
            const_cast<SmartPointer<T>&>(sp).m_pointer = NULL;
        }

        return *this;
    }

    bool isNull()
    {
        return (NULL == m_pointer);
    }

    T* get()
    {
        return m_pointer;
    }

    ~SmartPointer()
    {
        if(m_pointer)
        {
            delete m_pointer;
            m_pointer = NULL;
        }
    }
};
}

#endif // SMARTPOINTER_H
