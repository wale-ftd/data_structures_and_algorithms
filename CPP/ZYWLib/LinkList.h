#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DSaALib {

template <typename T>
class LinkList: public List<T>
{
protected:
    struct Node: public Object {
      T value;
      Node *next;
    };

#if 1
    /* 注意：这里也要继承自Object，否则匿名类和struct Node在内存里的布局可以不同。 */
    mutable struct : public Object {
        s8 reserved[sizeof(T)];
        Node *next;
    } m_header;
#else
    /* 这样定义的头节点是用隐患的 */
    mutable Node m_header;
#endif
    s32 m_length; /* 可以将链表长度信息放入header.value里，这样就可以节省内存空间了。 */
    Node *m_cursor;
    s32 m_cursor_step;

public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
        m_cursor = NULL;
        m_cursor_step = 1;
    }

    bool insert(s32 i, const T& e)
    {
        /* 链表是不是可以不判断位置合法性呢？ */
        bool ret = (0<=i) && (m_length>=i);
#if 0
        if(0 > i)
        {
            i = 0;
        }else if(m_length < i)
        {
            i = m_length;
        }
#endif

        if(ret)
        {
            Node *n_node = create();
            if(n_node)
            {
#if 1
                Node *cur = position(i);

                n_node->value = e;
                n_node->next = cur->next;
#else
                Node *cur = m_header.next;

                if(!cur)
                {
                    n_node->value = e;
                    n_node->next = NULL;
                }
                else
                {
                    for(s32 j = 0; cur->next && (j < i); cur = cur->next, j++) {}

                    n_node->value = e;
                    n_node->next = cur->next;
                }
#endif
                cur->next = n_node;

                m_length++;
            }
            else
            {
                ret = false;

                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert LinkList node ...");
            }
        }

        return ret;
    }

    bool insert(const T& e)    /* 尾插 */
    {
        return insert(m_length, e);
    }

    bool remove(s32 i)
    {
        bool ret = (0<=i) && (m_length>i);

        if(ret)
        {
            Node *cur = position(i);

            Node *t_node = cur->next;

            if(m_cursor == t_node)
            {
                m_cursor = t_node->next;
            }

            cur->next = t_node->next;

            /* 为确保remove是异常安全(防止destroy时调用自定义类型的析构函数抛出异常时，
               m_length还是正确)的，m_length--必须放在destroy前面。
             */
            m_length--;

            if(t_node)
            {
                destroy(t_node);
            }
        }

        return ret;
    }

    bool set(s32 i, const T& e)
    {
        bool ret = (0<=i) && (m_length>i);

        if(ret)
        {
            position(i)->next->value = e;
        }

        return ret;
    }

    bool get(s32 i, T& e) const
    {
        bool ret = (0<=i) && (m_length>i);

        if(ret)
        {
            e= position(i)->next->value;    /* const成员函数只能调用const成员函数，否则会编译报错 */
        }

        return ret;
    }

    T get(s32 i) const
    {
        T ret;

        if(!get(i, ret))
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }

        return ret;
    }

    s32 find(const T& e) const
    {
        s32 ret = -1;
        Node *cur = m_header.next;

        for(s32 i = 0; cur; cur = cur->next, i++)
        {
            if(cur->value == e)
            {
                ret = i;

                break;
            }
        }

        return ret;
    }

    s32 length() const
    {
        return m_length;
    }

    void clear()
    {
#if 1
        while(m_header.next)
        {
            Node *t_node = m_header.next;

            m_header.next = t_node->next;

            /* 为确保clear是异常安全(防止destroy时调用自定义类型的析构函数抛出异常时，
               m_length还是正确)的，m_length--必须放在destroy前面。
             */
            m_length--;

            if(t_node)
            {
                destroy(t_node);
            }
        }
#else
        for(s32 i = 0; i < length(); remove(0), i++) {}
#endif
    }

    bool move(s32 i, s32 step = 1)
    {
        bool ret = (0<=i) && (length()>i) && (0<step);

        if(ret)
        {
            m_cursor = position(i)->next;

            m_cursor_step = step;
        }

        return ret;
    }

    bool end()
    {
        return (NULL == m_cursor);
    }

    T current()
    {
        T ret;

        if(!end())
        {
            ret = m_cursor->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at the current position ...");
        }

        return ret;
    }

    bool next()
    {
        s32 i = 0;

        for(; (i<m_cursor_step) && m_cursor; m_cursor = m_cursor->next, i++) {}

        return (i == m_cursor_step);
    }

    ~LinkList()
    {
        clear();
    }

protected:
    /* 定位到i的前一个。所以定位到第i个元素的使用方法是：position()->next */
    Node *position(s32 i) const
    {
        /* 编译报错。在const成员函数里，不准修改任何成员变量的值。在这里
           对成员变量取地址，编译器会认为你可以会修改成员变量的值。
         * 解决方案：用mutable修改m_header成员变量。
         */
        Node *ret = reinterpret_cast<Node *>(&m_header);

        for(s32 j = 0; j < i; ret = ret->next, j++) {}

        return ret;
    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node *pn)
    {
        if(pn)
        {
            delete pn;
        }
    }
};

}

#endif // LINKLIST_H
