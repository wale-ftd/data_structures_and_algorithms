#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace ZYWLib
{
template <typename T>
class SmartPointer: public Pointer<T>
{
public:
    SmartPointer(T* p = NULL): Pointer<T>(p)
    {
    }

    SmartPointer(const SmartPointer<T>& sp)
    {
        if(this->m_pointer)
        {
            delete this->m_pointer;
            this->m_pointer = NULL;
        }

        this->m_pointer = sp.m_pointer;
        const_cast<SmartPointer<T>&>(sp).m_pointer = NULL;
    }

    SmartPointer<T>& operator =(const SmartPointer<T>& sp)
    {
        if(this != &sp)
        {
            T *p_tmp = this->m_pointer;

            this->m_pointer = sp.m_pointer;
            const_cast<SmartPointer<T>&>(sp).m_pointer = NULL;

            if(p_tmp)
            {
                delete p_tmp;
            }
        }

        return *this;
    }

    ~SmartPointer()
    {
        if(this->m_pointer)
        {
            delete this->m_pointer;
            this->m_pointer = NULL;
        }
    }
};
}

#endif // SMARTPOINTER_H
