#include <iostream>
#include "BTree.h"


using namespace std;
using namespace DSaALib;

#define BTREE_NODE_NON_PARENT

/**
 * delOdd - 删除node为根结点的二叉树中的单度结点，树结点有父指针
 */
template<typename T>
static BTreeNode<T>* delOdd(BTreeNode<T>* node)
{
    BTreeNode<T>* ret = NULL;

    if(node)
    {
        if((node->left&&(!node->right)) ||
           ((!node->left)&&node->right))
        {
            BTreeNode<T>* child = node->left ? node->left : node->right;
            BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
            if(parent)
            {
#if 0
                if(parent->left == node)
                {
                    parent->left = child;
                }
                else
                {
                    parent->right = child;
                }
#else
                BTreeNode<T>*& parent_child = (node==parent->left) ? parent->left : parent->right;
                parent_child = child;
#endif
            }

            child->parent = parent;

            if(node->flag())
            {
                delete node;
            }

            ret = delOdd(child);
        }
        else
        {
            delOdd(node->left);
            delOdd(node->right);

            ret = node;
        }
    }

    return ret;
}

/**
 * delOddNonParent - 删除node为根结点的二叉树中的单度结点，树结点没有父指针
 */
template<typename T>
static BTreeNode<T>* delOddNonParent(BTreeNode<T>*& node)  /* 注意node的类型。或者传二重指针 */
{
    BTreeNode<T>* ret = NULL;

    if(node)
    {
        if((node->left&&(!node->right)) ||
           ((!node->left)&&node->right))
        {
            BTreeNode<T>* child = node->left ? node->left : node->right;

            if(node->flag())
            {
                delete node;
            }

            node = child;

            ret = delOddNonParent(node);
        }
        else
        {
            delOddNonParent(node->left);
            delOddNonParent(node->right);

            ret = node;
        }
    }

    return ret;
}

/**
 * inOrderThread1_func - 中序线索化方法1的功能函数
 * @node: 根结点，也是中序访问的结点
 * @pre:  为中序遍历时的前驱结点指针
 */
template <typename T>
static void inOrderThread1_func(BTreeNode<T>* node, BTreeNode<T>*& pre)
{
    if(node)
    {
        inOrderThread1_func(node->left, pre);

        node->left = pre;

        if(pre)
        {
            pre->right = node;
        }

        pre = node;

        inOrderThread1_func(node->right, pre);
    }
}

template <typename T>
static BTreeNode<T>* inOrderThread1(BTreeNode<T>* node)
{
    BTreeNode<T>* pre = NULL;

    inOrderThread1_func(node, pre);

    while(node && node->left)
    {
        node = node->left;
    }

    return node;
}

/**
 * inOrderThread2_func - 中序线索化方法2的功能函数
 * @node: 根结点，也是中序访问的结点
 * @head:    转换成功后指向双向链表的首结点
 * @tail:    转换成功后指向双向链表的尾结点
 */
template <typename T>
static void inOrderThread2_func(BTreeNode<T>* node, BTreeNode<T>*& head, BTreeNode<T>*& tail)
{
    if(node)
    {
        BTreeNode<T>* h = NULL;
        BTreeNode<T>* t = NULL;

        inOrderThread2_func(node->left, h, t);
        node->left = t;
        if(t)
        {
            t->right = node;
        }

        head = h ? h : node;

        h = NULL;
        t = NULL;

        inOrderThread2_func(node->right, h, t);
        node->right = h;
        if(h)
        {
            h->left = node;
        }

        tail = t ? t : node;
    }
}

template <typename T>
static BTreeNode<T>* inOrderThread2(BTreeNode<T>* node)
{
    BTreeNode<T>* h = NULL;
    BTreeNode<T>* t = NULL;

    inOrderThread2_func(node, h, t);

    return h;
}

template < typename T >
BTreeNode<T>* createTree()
{
    static BTreeNode<s32> ns[9];

    for(s32 i=0; i<9; i++)
    {
        ns[i].value = i;
        ns[i].parent = NULL;
        ns[i].left = NULL;
        ns[i].right = NULL;
    }

    ns[0].left = &ns[1];
    ns[0].right = &ns[2];
    ns[1].parent = &ns[0];
    ns[2].parent = &ns[0];

    ns[1].left = &ns[3];
    ns[1].right = NULL;
    ns[3].parent = &ns[1];

    ns[2].left = &ns[4];
    ns[2].right = &ns[5];
    ns[4].parent = &ns[2];
    ns[5].parent = &ns[2];

    ns[3].left = NULL;
    ns[3].right = &ns[6];
    ns[6].parent = &ns[3];

    ns[4].left = &ns[7];
    ns[4].right = NULL;
    ns[7].parent = &ns[4];

    ns[5].left = &ns[8];
    ns[5].right = NULL;
    ns[8].parent = &ns[5];

    return ns;
}

template < typename T >
void printInOrder(BTreeNode<T>* node)
{
    if( node != NULL )
    {
        printInOrder(node->left);

        cout << node->value <<" ";

        printInOrder(node->right);
    }
}

template < typename T >
void printDualList(BTreeNode<T>* node)
{
    BTreeNode<T>* g = node;

    cout << "head -> tail: " << endl;

    while( node != NULL )
    {
        cout << node->value << " ";

        g = node;

        node = node->right;
    }

    cout << endl;

    cout << "tail -> head: " << endl;

    while( g != NULL )
    {
        cout << g->value << " ";

        g = g->left;
    }

    cout << endl;
}

s32 main(s32 argc, s8** argv)
{
    BTreeNode<s32>* ns = createTree<s32>();

    cout << "原始树中序遍历" << endl;
    printInOrder(ns);
    cout << endl;
    cout << endl;

#ifndef BTREE_NODE_NON_PARENT
    cout << "删除单度结点后的树---树结点带父指针" << endl;
    ns = delOdd(ns);
#else
    cout << "删除单度结点后的树---树结点不带父指针" << endl;
    ns = delOddNonParent(ns);
#endif
    printInOrder(ns);
    cout << endl;
    cout << endl;

#ifndef BTREE_NODE_NON_PARENT
    cout << "验证父指针是否处理有效" << endl;
    s32 a[] = {6, 7, 8};
    for(s32 i = 0; i < (sizeof(a)/sizeof(a[0])); i++)
    {
        TreeNode<s32> *n = ns + a[i];

        while(n)
        {
            cout << n->value;

            n = n->parent;
            if(n)
            {
                cout << "->";
            }
        }

        cout << endl;
    }
    cout << endl;
#endif

    cout << "中序遍历线索化" << endl;
    //ns = inOrderThread1(ns);
    ns = inOrderThread2(ns);
    printDualList(ns);

    return 0;
}

