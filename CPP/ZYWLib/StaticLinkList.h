#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

NAMESPACE_DEF_START(ZYWLib)

template <typename T, int N>
class StaticLinkList: public LinkList<T>
{
protected:
    /**
     * 1. ����Node�õ�T������Ҫ����LinkList<T>���ֱ�
     * 2. LinkList<T>::Node���������ñ������ֱ��Node���������ͻ���
          ��̬��Ա���������Ի�Ҫ����typename�����߱������������Ͳ��Ǿ�
          ̬��Ա������
     */
    typedef typename LinkList<T>::Node Node;

    struct SNode: public Node
    {
        void* operator new(ZYW_UINT32 size, void *loc)
        {
            (void)size; /* ����������� */

            return loc;
        }
    };

    ZYW_UINT8 m_space[N * sizeof(SNode)];
    ZYW_BOOL m_used[N];

public:
    StaticLinkList()
    {
        for(ZYW_INT32 i = 0; i < N; i++)
        {
            m_used[i] = false;
        }
    }

    ZYW_INT32 capacity()
    {
        return N;
    }

protected:
    SNode* create()
    {
        SNode *ret = NULL;

        for(ZYW_INT32 i = 0; i < N; i++)
        {
            if(!m_used[i])
            {
                ret = reinterpret_cast<SNode *>(m_space) + i;
                /* ��������𣿲�û�У�����ֻ�Ƿ����˿ռ���ѣ���û�д�������Ŷ����Ϊ��
                 * û���������õ�Node.value�Ĺ��캯����
                 * ����ô����Node.value�Ĺ��캯���أ�Ҫ����Node��new��������Ȼ����ʾ���á�
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

        for(ZYW_INT32 i = 0; i < N; i++)
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

NAMESPACE_DEF_END

#endif // STATICLINKLIST_H
