#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DSaALib {

template <typename T>
class TreeNode: public Object
{
public:
    T value;
    /**
     * 教科书里都不会要求树结点里面要有指向该树结点的父结点。从理论上来
     * 说，这是没有任何问题的。但对于工程实践，加上这个父结点的指针是非常
     * 有帮助的。
     */
    TreeNode<T> *parent;

    TreeNode()
    {
        parent = NULL;
    }

    virtual ~TreeNode() = 0;    /* 表明TreeNode类是一个抽象类 */
};

/* 虽然析构函数已经是一个纯虚函数了，但还是要给它提供一个空的函数体，否则，可能会编译不过。 */
template <typename T>
TreeNode<T>::~TreeNode()
{
}

}

#endif // TREENODE_H
