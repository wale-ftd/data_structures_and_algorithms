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
     * �̿����ﶼ����Ҫ�����������Ҫ��ָ��������ĸ���㡣����������
     * ˵������û���κ�����ġ������ڹ���ʵ�����������������ָ���Ƿǳ�
     * �а����ġ�
     */
    TreeNode<T> *parent;

    TreeNode()
    {
        parent = NULL;
    }

    virtual ~TreeNode() = 0;    /* ����TreeNode����һ�������� */
};

/* ��Ȼ���������Ѿ���һ�����麯���ˣ�������Ҫ�����ṩһ���յĺ����壬���򣬿��ܻ���벻���� */
template <typename T>
TreeNode<T>::~TreeNode()
{
}

}

#endif // TREENODE_H
