#include <iostream>
#include "BTree.h"


using namespace std;
using namespace DSaALib;

/* 树结点有父指针 */
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

/* 树结点没有父指针 */
template<typename T>
static BTreeNode<T>* delOddNonParent(BTreeNode<s32>* node)
{

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
void prs32InOrder(BTreeNode<T>* node)
{
    if( node != NULL )
    {
        prs32InOrder(node->left);

        cout << node->value <<" ";

        prs32InOrder(node->right);
    }
}

template < typename T >
void prs32DualList(BTreeNode<T>* node)
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

    cout << "原始树" << endl;
    prs32InOrder(ns);
    cout << endl;
    cout << endl;

    cout << "删除单度结点后的树---树结点带父指针" << endl;
    ns = delOdd(ns);
    prs32InOrder(ns);
    cout << endl;
    cout << endl;

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

    return 0;
}

