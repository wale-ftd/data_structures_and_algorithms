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

protected:
    bool m_flag;

public:
    TreeNode()
    {
        parent = NULL;
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;    /* ����TreeNode����һ�������� */

protected:
    /* ͨ�����������ǲ��ܱ���ֵ�� */
    TreeNode(const TreeNode<T> &);
    TreeNode<T>& operator =(const TreeNode<T> &);

    void* operator new(u32 size) throw()
    {
        return Object::operator new(size);
    }
};

/* ��Ȼ���������Ѿ���һ�����麯���ˣ�������Ҫ�����ṩһ���յĺ����壬���򣬿��ܻ���벻���� */
template <typename T>
TreeNode<T>::~TreeNode()
{
}

}

#endif // TREENODE_H
