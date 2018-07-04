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

public:
    static GTreeNode<T> *NewNode()
    {
        GTreeNode<T> *ret = new GTreeNode<T>();

        if(ret)
            ret->m_flag = true;

        return ret;
    }
};


}


#endif // GTREENODE_H
