#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace DSaALib {

enum BT_NODE_POS {
    BTNP_ANY,
    BTNP_LEFT,
    BTNP_RIGHT
};

template<typename T>
class BTreeNode: public TreeNode<T>
{
public:
    BTreeNode<T> *left;
    BTreeNode<T> *right;

public:
    BTreeNode()
    {
        left  = NULL;
        right = NULL;
    }

    static BTreeNode<T> *NewNode()
    {
        BTreeNode<T> *ret = new BTreeNode<T>();

        if(ret)
            ret->m_flag = true;

        return ret;
    }
};

}


#endif // BTREENODE_H
