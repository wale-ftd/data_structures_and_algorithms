#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"


NAMESPACE_DEF_START(ZYWLib)

template <typename T>
class GTreeNode: public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>*> child;

};


NAMESPACE_DEF_END


#endif // GTREENODE_H
