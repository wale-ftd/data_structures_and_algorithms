#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DSaALib {

template <typename T, s32 N>
class StaticStack: public Stack<T>
{
protected:
    T m_space[N];  /* ջ�洢�ռ䣬NΪģ����� */
    s32 m_top;     /* ջ����ʶ */
    s32 m_size;    /* ��ǰջ�Ĵ�С */

public:
    StaticStack()  /* O(1) */
    {
        m_top = -1;
        m_size = 0;
    }

    void push(const T& e)  /* O(1) */
    {
        if(N > m_size)
        {
            /**
             * Ϊʲô����m_space[++m_top]?
             * ��Ϊ���쳣��ȫ��e�Ƿ�ָ���ͣ�����e�������ͣ���e�ĸ�ֵ������bug��
             *    ������ô m_space[++m_top] = e���ͻ�����⣬�Ӷ�Ӱ�쵽m_top��
             *    ֵ�������ʹ�� m_space[m_top + 1] = e����ʹe�ĸ�ֵ������bug
             *    Ҳ����Ӱ�쵽m_top��ֵ��
             */
            m_space[m_top + 1] = e;
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack ...");
        }
    }

    void pop()  /* O(1) */
    {
        if(0 < m_size)
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top() const  /* O(1) */
    {
        if(0 < m_size)
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    void clear()  /* O(1) */
    {
        m_top = -1;
        m_size = 0;
    }

    s32 size() const  /* O(1) */
    {
        return m_size;
    }

    s32 capacity() const  /* O(1) */
    {
        return N;
    }
};

}

#endif // STATICSTACK_H
