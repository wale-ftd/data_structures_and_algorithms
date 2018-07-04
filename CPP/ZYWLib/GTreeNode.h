#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"


namespace DSaALib {

template <typename T>
class GTreeNode: public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>*> child;

protected:
    bool m_flag;

public:
    GTreeNode()
    {
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }

    static GTreeNode<T> *NewNode()
    {
        GTreeNode<T> *ret = new GTreeNode<T>();

        if(ret)
            ret->m_flag = true;

        return ret;
    }

protected:
    /* 通用树结点对象是不能被赋值的 */
    GTreeNode(const GTreeNode<T> &);
    GTreeNode<T>& operator =(const GTreeNode<T> &);

    void* operator new(u32 size) throw()
    {
        return Object::operator new(size);
    }
};


}


#endif // GTREENODE_H
