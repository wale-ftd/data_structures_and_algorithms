#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DSaALib {

template <typename T, s32 N>
class StaticStack: public Stack<T>
{
protected:
    T m_space[N];  /* 栈存储空间，N为模板参数 */
    s32 m_top;     /* 栈顶标识 */
    s32 m_size;    /* 当前栈的大小 */

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
             * 为什么不是m_space[++m_top]?
             * 答：为了异常安全。e是泛指类型，假如e是类类型，又e的赋值操作有bug的
             *    话，那么 m_space[++m_top] = e，就会出问题，从而影响到m_top的
             *    值；而如果使用 m_space[m_top + 1] = e，即使e的赋值操作有bug
             *    也不会影响到m_top的值。
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
