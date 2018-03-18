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

        return ret;
    }

    bool insert(const T& value, TreeNode<T> *parent)
    {
        bool ret = true;

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
     * 1. 与Tree.h相比，将返回值类型修改成了GTreeNode，合法吗？
     *    当然合法，因为赋值兼容性原则。
     * 2. const成员函数？
     *    意味着当前函数不会修改对象的状态，即在当前函数里不会修改任何成员
     *    变量的值。
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
