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
    /* 构造函数都可以不需要 */

    void push(const T& e)
    {
        m_list.insert(0, e);
    }

    void pop()
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

    T top() const
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

    void clear()
    {
        m_list.clear();
    }

    s32 size() const
    {
        return m_list.length();
    }
};

}

#endif // LINKSTACK_H
