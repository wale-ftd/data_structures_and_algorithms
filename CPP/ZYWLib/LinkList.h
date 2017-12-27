#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

NAMESPACE_DEF_START(ZYWLib)

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
        ZYW_INT8 reserved[sizeof(T)];
        Node *next;
    } m_header;
#else
    /* 这样定义的头节点是用隐患的 */
    mutable Node m_header;
#endif
    ZYW_INT32 m_length; /* 可以将链表长度信息放入header.value里，这样就可以节省内存空间了。 */

public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
    }

    ZYW_BOOL insert(ZYW_INT32 i, const T& e)
    {
        /* 链表是不是可以不判断位置合法性呢？ */
        ZYW_BOOL ret = (0<=i) && (m_length>=i);
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
            Node *n_node = (Node *)new Node();
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
                    for(ZYW_INT32 j = 0; cur->next && (j < i); cur = cur->next, j++) {}

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

    ZYW_BOOL insert(const T& e)    /* 尾插 */
    {
        return insert(m_length, e);
    }

    ZYW_BOOL remove(ZYW_INT32 i)
    {
        ZYW_BOOL ret = (0<=i) && (m_length>i);

        if(ret)
        {
            Node *cur = position(i);

            Node *t_node = cur->next;

            cur->next = t_node->next;

            m_length--;

            if(t_node)
            {
                delete t_node;
            }
        }

        return ret;
    }

    ZYW_BOOL set(ZYW_INT32 i, const T& e)
    {
        ZYW_BOOL ret = (0<=i) && (m_length>i);

        if(ret)
        {
            position(i)->next->value = e;
        }

        return ret;
    }

    ZYW_BOOL get(ZYW_INT32 i, T& e) const
    {
        ZYW_BOOL ret = (0<=i) && (m_length>i);

        if(ret)
        {
            e= position(i)->next->value;    /* const成员函数只能调用const成员函数，否则会编译报错 */
        }

        return ret;
    }

    T get(ZYW_INT32 i) const
    {
        T ret;

        if(!get(i, ret))
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }

        return ret;
    }

    ZYW_INT32 length() const
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

            if(t_node)
            {
                delete t_node;
            }
        }

        m_length = 0;
#else
        for(ZYW_INT32 i = 0; i < length(); remove(0), i++) {}
#endif
    }

    ~LinkList()
    {
        clear();
    }

protected:
    Node *position(ZYW_INT32 i) const
    {
        /* 编译报错。在const成员函数里，不准修改任何成员变量的值。在这里
           对成员变量取地址，编译器会认为你可以会修改成员变量的值。
         * 解决方案：用mutable修改m_header成员变量。
         */
        Node *ret = reinterpret_cast<Node *>(&m_header);

        for(ZYW_INT32 j = 0; j < i; ret = ret->next, j++) {}

        return ret;
    }
};

NAMESPACE_DEF_END

#endif // LINKLIST_H
