#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include <cstdlib>
#include "Exception.h"

namespace DSaALib {

template<typename T>
class SharedPointer: public Pointer<T>
{
private:
    s32 *m_ref;

    void assign(const SharedPointer<T>& obj)
    {
        m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if(m_ref)
        {
            (*m_ref)++;
        }
    }

public:
    SharedPointer(T *p = NULL): m_ref(NULL)
    {
        if(p)
        {
            m_ref = static_cast<s32 *>(std::malloc(sizeof(s32)));
            if(m_ref)
            {
                *m_ref = 1;

                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create SharedPointer object ...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj): Pointer<T>(NULL)
    {
        assign(obj);
    }

    SharedPointer<T>& operator =(const SharedPointer<T>& obj)
    {
        if(this != &obj)
        {
            clear();    /* 如果sharedpointer已经指向了对象，要先清空。 */

            assign(obj);
        }

        return *this;
    }

    void clear()
    {
        s32 *ref_tmp = m_ref;
        T *pointer_tmp = this->m_pointer;

        m_ref = NULL;
        this->m_pointer = NULL;

        if(ref_tmp)
        {
            (*ref_tmp)--;

            if(!(*ref_tmp))
            {
                free(ref_tmp);

                if(pointer_tmp)
                {
                    delete pointer_tmp;
                }
            }
        }
    }

    ~SharedPointer()
    {
        clear();
    }
};

template <typename T>
bool operator ==(const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (l.get() == r.get());
}

template <typename T>
bool operator !=(const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (!(l==r));
}

}

#endif // SHAREDPOINTER_H
