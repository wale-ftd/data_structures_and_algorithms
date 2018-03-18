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
     * ��Ʒ����в���˵��Ҫһ��������������virtual ~Pointer() = 0��Ϊʲô��
       ����û���ṩ?��ΪPointer�̳���Object�࣬Object����һ������������������
       �ԣ�ֻҪPointerû��ʵ�ִ���������������Pointer�ͻ���һ�������࣬��Ҳ��û
       ��Ҫ��дһ�鴿�����������ˡ�
     */
};

}

#endif // POINTER_H
