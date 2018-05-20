#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"

namespace DSaALib {

template <typename T>
class GTree: public Tree<T>
{
public:
    bool insert(TreeNode<T> *node)
    {
        bool ret = true;

        if(node)
        {
            if(this->m_root)
            {
                GTreeNode<T> *p_pn = find(node->parent);

                if(p_pn)
                {
                    /* �жϸø��ڵ��£��Ƿ����������ڵ���ͬ�Ľڵ㣬��ֹ�ظ����롣 */
                    GTreeNode<T> *p_cn = dynamic_cast<GTreeNode<T>*>(node);

                    /* Ϊʲô��ֱ��find(p_cn)��������p_pn->child.find(p_cn)�أ�
                     * ��Ҫ�Ǵ�Ч�ʷ��濼�ǡ���Ϊfind()�Ǵ�������ʼ���ң������������Ѿ�
                     * �ж��˴�����ڵ�ĸ��ڵ��Ѿ������ˣ����ԣ����ڸ��ڵ���ӽڵ�������
                     * ���Ҽ��ɣ�û�б�Ҫ�ٴ���������ʼ���ҡ�
                     */
                    if(0 > p_pn->child.find(p_cn))
                    {
                        p_pn->child.insert(p_cn);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "Invalid parent tree node ...");
                }
            }
            else
            {
                node->parent = NULL;
                this->m_root = node;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot be NULL ...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T> *parent)
    {
        bool ret = true;
        GTreeNode<T> *p_n = new GTreeNode<T>();

        if(p_n)
        {
            p_n->parent = parent;
            p_n->value = value;

            ret = insert(p_n);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create new tree node ...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        return NULL;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T> *node)
    {
        return NULL;
    }

    /**
     * 1. ��Tree.h��ȣ�������ֵ�����޸ĳ���GTreeNode���Ϸ���
     *    ��Ȼ�Ϸ�����Ϊ��ֵ������ԭ��
     * 2. const��Ա������
     *    ��ζ�ŵ�ǰ���������޸Ķ����״̬�����ڵ�ǰ�����ﲻ���޸��κγ�Ա
     *    ������ֵ��
     */
    GTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T>* find(TreeNode<T> *node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    s32 count() const
    {
        return 0;
    }

    s32 degree() const
    {
        return 0;
    }

    s32 height() const
    {
        return 0;
    }

    void clear()
    {
        this->m_root = NULL;
    }

    ~GTree()
    {
        clear();
    }

protected:
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if(node)
        {
            if(value == node->value)
            {
                ret = node;
            }
            else
            {
                for(node->child.move(0); (!node->child.end()) && (!ret); node->child.next())
                {
                    ret = find(node->child.current(), value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;

        if(obj == node)
        {
            ret = node;
        }
        else
        {
            if(node)
            {
                for(node->child.move(0); (!node->child.end()) && (!ret); node->child.next())
                {
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }
};

}



#endif // GTREE_H
