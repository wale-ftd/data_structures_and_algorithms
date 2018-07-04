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
        return NULL;

    }

    TreeNode<T>* find(TreeNode<T> *node) const
    {
        return NULL;

    }

    TreeNode<T>* root() const
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
};

}


#endif // BTREE_H
