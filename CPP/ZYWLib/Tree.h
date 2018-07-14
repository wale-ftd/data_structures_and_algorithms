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
     * 1. 两个>>之间要有空格隔开，否则，会被误认为是右移操作符，编译不过。
     * 2. 删除操作为什么要返回SharedPointer< Tree<T> >?
     *   答：根据定义，删除操作删除的是一个结点。但大家想一想，如果只删除这
     *      个结点，那该结点的孩子、子孙们该怎么处理呢？处理方式有很多种，
     *      没有唯一的处理方式，只有比较合理的处理方式。个人认为比较合理的
     *      处理方式是：删除一个结点后，它的孩子、子孙们也要全部删除。这样
     *      做有点简单粗暴了吧。是的，那就来一个折中的方案吧。这个方案就是：
     *      如果要删除一个结点，就是将该结点所代表的子树从原来的树中移除(只
     *      是移除，并不是立刻销毁该子树)，并返回该子树。返回了该子树，那就
     *      可以对该结点的孩子、子孙们做进一步的处理了，既可以将它们添加加树
     *      中，也可以将它们直接销毁。所以删除操作返回的是用SharedPointer
     *      指向的一颗树。
     */
    virtual SharedPointer< Tree<T> > remove(const T& value) = 0;
    virtual SharedPointer< Tree<T> > remove(TreeNode<T> *node) = 0;
    virtual TreeNode<T>* find(const T& value) const = 0;
    virtual TreeNode<T>* find(TreeNode<T> *node) const = 0;
    virtual TreeNode<T>* root() const = 0;
    /* 计算树中结点的数目 */
    virtual s32 count() const = 0;
    /* 获取树的度 */
    virtual s32 degree() const = 0;
    /* 计算树的高度 */
    virtual s32 height() const = 0;
    /* 将树中的所有结点清除 */
    virtual void clear() = 0;

    /*
     * 层次遍历树所用到的四个函数。
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
    /* 树对象是不能被赋值的 */
    Tree(const Tree<T> &);
    Tree<T>& operator =(const Tree<T> &);
};

}


#endif // TREE_H
