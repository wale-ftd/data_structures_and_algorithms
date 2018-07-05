#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "LinkQueue.h"

namespace DSaALib {

template <typename T>
class BTree: public Tree<T>
{
public:
    bool insert(TreeNode<T> *node)
    {
        return true;
    }

    bool insert(const T& value, TreeNode<T> *parent)
    {
        return true;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        return NULL;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T> *node)
    {
        return NULL;

    }

    TreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    TreeNode<T>* find(TreeNode<T> *node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
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

    /* 将树中的所有结点清除 */
    void clear()
    {
        this->m_root = NULL;
    }

    ~BTree()
    {
        clear();
    }

protected:
    /* virtual */ BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const
    {
        BTreeNode<T>* ret = NULL;

        if(node)
        {
            if(value == node->value)
            {
                ret = node;
            }
            else
            {
                if(!ret)
                {
                    ret = find(node->left, value);
                }

                if(!ret)
                {
                    ret = find(node->right, value);
                }
            }
        }

        return ret;
    }

    /* virtual */ BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T> *obj) const
    {
        BTreeNode<T>* ret = NULL;

        if(node)
        {
            if(obj == node)
            {
                ret = node;
            }
            else
            {
                if(!ret)
                {
                    ret = find(node->left, obj);
                }

                if(!ret)
                {
                    ret = find(node->right, obj);
                }
            }
        }

        return ret;
    }
};

}


#endif // BTREE_H
