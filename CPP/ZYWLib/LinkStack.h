#ifndef LINKSTACK_H
#define LINKSTACK_H


#include "Stack.h"
#include "LinkList.h"

#undef _TAIL_
//#define _TAIL_

namespace DSaALib {

template <typename T>
class LinkStack: public Stack<T>
{
protected:
    LinkList<T> m_list;

public:
    /* 构造函数都可以不需要 */

    void push(const T& e)  /* O(1) */
    {
#ifndef _TAIL_
        m_list.insert(0, e);
#else
        m_list.insert(e);
#endif
    }

    void pop()  /* O(1) */
    {
        if(0 < m_list.length())
        {
#ifndef _TAIL_
            m_list.remove(0);
#else
            m_list.remove(m_list.length()-1);
#endif
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
#ifndef _TAIL_
            return m_list.get(0);
#else
            return m_list.get(m_list.length()-1);
#endif
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
