#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "Exception.h"
#include "LinuxList.h"


namespace DSaALib {

template<typename T>
class LinkQueue: public Queue<T>
{
protected:
    struct Node: public Object
    {
        list_head head;
        T value;
    };
    list_head m_header;
    s32 m_length;

public:
    LinkQueue()  /* O(1) */
    {
        m_length = 0;

        INIT_LIST_HEAD(&m_header);
    }

    void add(const T &e)  /* O(1) */
    {
        Node *node = new Node();
        if(node)
        {
            node->value = e;

            list_add_tail(&node->head, &m_header);

            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add new element ...");
        }
    }

    void remove()  /* O(1) */
    {
        if(0 < m_length)
        {
            list_head *to_del = m_header.next;

            list_del(to_del);

            m_length--;

            delete list_entry(to_del, Node, head);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T front() const  /* O(1) */
    {
        if(0 < m_length)
        {
            return list_entry(m_header.next, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void clear()  /* O(n) */
    {
        while(0 < m_length)
        {
            remove();
        }
    }

    s32 length() const  /* O(1) */
    {
        return m_length;
    }

    ~LinkQueue()  /* O(n) */
    {
        clear();
    }
};

}


#endif // LINKQUEUE_H
