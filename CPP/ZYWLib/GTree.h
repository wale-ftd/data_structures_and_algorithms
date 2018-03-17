#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"

NAMESPACE_DEF_START(ZYWLib)

template <typename T>
class GTree: public Tree<T>
{
public:
    ZYW_BOOL insert(TreeNode<T> *node)
    {
        ZYW_BOOL ret = true;

        return ret;
    }

    ZYW_BOOL insert(const T& value, TreeNode<T> *parent)
    {
        ZYW_BOOL ret = true;

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
     * 与Tree.h相比，将返回值类型修改成了GTreeNode，合法吗？
     * 当然合法，因为赋值兼容性原则。
     */
    GTreeNode<T>* find(const T& value) const
    {
        return NULL;
    }

    GTreeNode<T>* find(TreeNode<T> *node) const
    {
        return NULL;
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    ZYW_INT32 count() const
    {
        return 0;
    }

    ZYW_INT32 degree() const
    {
        return 0;
    }

    ZYW_INT32 height() const
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
};

NAMESPACE_DEF_END



#endif // GTREE_H
