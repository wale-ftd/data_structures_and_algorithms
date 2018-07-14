#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include "SharedPointer.h"

namespace DSaALib {

template <typename T>
class Tree: public Object
{
protected:
    TreeNode<T> *m_root;

public:
    Tree()
    {
        m_root = NULL;
    }

    virtual bool insert(TreeNode<T> *node) = 0;
    virtual bool insert(const T& value, TreeNode<T> *parent) = 0;
    /**
     * 1. ����>>֮��Ҫ�пո���������򣬻ᱻ����Ϊ�����Ʋ����������벻����
     * 2. ɾ������ΪʲôҪ����SharedPointer< Tree<T> >?
     *   �𣺸��ݶ��壬ɾ������ɾ������һ����㡣�������һ�룬���ֻɾ����
     *      ����㣬�Ǹý��ĺ��ӡ������Ǹ���ô�����أ�����ʽ�кܶ��֣�
     *      û��Ψһ�Ĵ���ʽ��ֻ�бȽϺ���Ĵ���ʽ��������Ϊ�ȽϺ����
     *      ����ʽ�ǣ�ɾ��һ���������ĺ��ӡ�������ҲҪȫ��ɾ��������
     *      ���е�򵥴ֱ��˰ɡ��ǵģ��Ǿ���һ�����еķ����ɡ�����������ǣ�
     *      ���Ҫɾ��һ����㣬���ǽ��ý���������������ԭ���������Ƴ�(ֻ
     *      ���Ƴ����������������ٸ�����)�������ظ������������˸��������Ǿ�
     *      ���ԶԸý��ĺ��ӡ�����������һ���Ĵ����ˣ��ȿ��Խ�������Ӽ���
     *      �У�Ҳ���Խ�����ֱ�����١�����ɾ���������ص�����SharedPointer
     *      ָ���һ������
     */
    virtual SharedPointer< Tree<T> > remove(const T& value) = 0;
    virtual SharedPointer< Tree<T> > remove(TreeNode<T> *node) = 0;
    virtual TreeNode<T>* find(const T& value) const = 0;
    virtual TreeNode<T>* find(TreeNode<T> *node) const = 0;
    virtual TreeNode<T>* root() const = 0;
    /* �������н�����Ŀ */
    virtual s32 count() const = 0;
    /* ��ȡ���Ķ� */
    virtual s32 degree() const = 0;
    /* �������ĸ߶� */
    virtual s32 height() const = 0;
    /* �����е����н����� */
    virtual void clear() = 0;

    /*
     * ��α��������õ����ĸ�������
     * eg: for(t.begin(); !t.end(); t.next)
     *     {
     *         cout << t.current() << " ";
     *     }
     *     cout << endl;
     */
    virtual bool begin() = 0;
    virtual bool end()   = 0;
    virtual bool next()  = 0;
    virtual T current()  = 0;

protected:
    /* �������ǲ��ܱ���ֵ�� */
    Tree(const Tree<T> &);
    Tree<T>& operator =(const Tree<T> &);
};

}


#endif // TREE_H
