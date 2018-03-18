#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace DSaALib {

template<typename T>
class Pointer: public Object
{
protected:
    T *m_pointer;

public:
    Pointer(T *p = NULL)
    {
        m_pointer = p;
    }

    T * operator ->()
    {
        return m_pointer;
    }

    const T * operator ->() const
    {
        return m_pointer;
    }

    T& operator *()
    {
        return *m_pointer;
    }

    const T& operator *() const
    {
        return *m_pointer;
    }

    bool isNull() const
    {
        return (NULL == m_pointer);
    }

    T * get() const
    {
        return m_pointer;
    }

    /**
     * 设计方案中不是说还要一个纯虚析构函数virtual ~Pointer() = 0吗？为什么在
       这里没有提供?因为Pointer继承了Object类，Object中有一个纯虚析构函数，所
       以，只要Pointer没有实现纯虚析构函数，那Pointer就还是一个抽象类，那也就没
       必要再写一遍纯虚析构函数了。
     */
};

}

#endif // POINTER_H
