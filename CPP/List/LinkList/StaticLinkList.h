#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace DSaALib {

template <typename T, int N>
class StaticLinkList: public LinkList<T>
{
protected:
    /**
     * 1. 由于Node用到T，所以要加上LinkList<T>来分辨
     * 2. LinkList<T>::Node还不足以让编译器分辨出Node到底是类型还是
          静态成员变量，所以还要加上typename来告诉编译器这是类型不是静
          态成员变量。
     */
    typedef typename LinkList<T>::Node Node;

    struct SNode: public Node
    {
        void* operator new(u32 size, void *loc)
        {
            (void)size; /* 消除警告而已 */

            return loc;
        }
    };

    u8 m_space[N * sizeof(SNode)];
    bool m_used[N];

public:
    StaticLinkList()
    {
        for(s32 i = 0; i < N; i++)
        {
            m_used[i] = false;
        }
    }

    s32 capacity()
    {
        return N;
    }

    ~StaticLinkList()
    {
        this->clear();  /* 这样就会调用StaticLinkList的destroy()了。否则调用的是LinkList中的destroy() */
    }

protected:
    SNode* create()
    {
        SNode *ret = NULL;

        for(s32 i = 0; i < N; i++)
        {
            if(!m_used[i])
            {
                ret = reinterpret_cast<SNode *>(m_space) + i;
                /* 这就完了吗？并没有，到此只是分配了空间而已，并没有创建对象哦。因为还
                 * 没有真正调用到Node.value的构造函数。
                 * 那怎么调用Node.value的构造函数呢？要重载Node的new操作符，然后显示调用。
                 */

                ret = new(ret)SNode();

                m_used[i] = true;

                break;
            }
        }

        return ret;
    }

    void destroy(Node *pn)
    {
        if(!pn)
        {
            return;
        }

        SNode *space = reinterpret_cast<SNode *>(m_space);
        SNode *psn = dynamic_cast<SNode *>(pn);

        for(s32 i = 0; i < N; i++)
        {
            if((space+i) == psn)
            {
                m_used[i] = false;

                psn->~SNode();

                break;
            }
        }
    }
};

}

#endif // STATICLINKLIST_H
