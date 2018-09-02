#ifndef LINKSTACK_H
#define LINKSTACK_H


#include "Stack.h"
#include "LinkList.h"


namespace DSaALib {

template <typename T>
class LinkStack: public Stack<T>
{
protected:
    LinkList<T> m_list;

public:
    /* ���캯�������Բ���Ҫ */

    void push(const T& e)  /* O(1) */
    {
        m_list.insert(0, e);
    }

    void pop()  /* O(1) */
    {
        if(0 < m_list.length())
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top() const  /* O(1) */
    {
        if(0 < m_list.length())
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    void clear()  /* O(n) */
    {
        m_list.clear();
    }

    s32 size() const  /* O(1) */
    {
        return m_list.length();
    }
};

}

#endif // LINKSTACK_H
