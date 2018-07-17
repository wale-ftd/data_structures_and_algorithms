#include <iostream>
#include <string.h>
#include "BTree.h"


using namespace std;
using namespace DSaALib;

s32 main(s32 argc, s8** argv)
{
    BTree<s32> bt;
    BTreeNode<s32>* pbtn = NULL;

    bt.insert(1, NULL);

    pbtn = bt.find(1);
    bt.insert(2, pbtn);
    bt.insert(3, pbtn);

    pbtn = bt.find(2);
    bt.insert(4, pbtn);
    bt.insert(5, pbtn);

    pbtn = bt.find(4);
    bt.insert(8, pbtn);
    bt.insert(9, pbtn);

    pbtn = bt.find(5);
    bt.insert(10, pbtn);

    pbtn = bt.find(3);
    bt.insert(6, pbtn);
    bt.insert(7, pbtn);

    cout << "----------------------------------" << endl;
    cout << "count  = " << bt.count() << endl;
    cout << "degree = " << bt.degree() << endl;
    cout << "height = " << bt.height() << endl;
    cout << endl;

    s32 ca[] = {8, 9, 10, 6, 7};

    cout << "----------------clone------------------" << endl;
    SharedPointer< BTree<s32> > bt_clone = bt.clone();
    for(u32 i = 0; i < (sizeof(ca)/sizeof(ca[0])); i++)
    {
        TreeNode<s32> *node = bt_clone->find(ca[i]);

        while(node)
        {
            cout << node->value << " ";

            node = node->parent;
        }

        cout << endl;
    }
    cout << endl;

    cout << "----------------compare bt with bt_clone------------------" << endl;
    cout << "bt == *bt_clone : " << (bt == *bt_clone) << endl;
    //cout << "bt == *bt_clone : " << (bt != *bt_clone) << endl;
    cout << endl;

    cout << "----------------levelorder------------------" << endl;
    for(bt.begin(); !bt.end(); bt.next())
    {
        cout << bt.current() << " ";
    }
    cout << endl;
    cout << endl;

    cout << "---------------preorder-------------------" << endl;
    SharedPointer< Array<s32> > spa = NULL;
    //spa = bt.traversal(BTT_PRE_ORDER);
    //spa = bt.traversal(BTT_IN_ORDER);
    spa = bt.traversal(BTT_POST_ORDER);
    for(s32 i = 0; i < (*spa).length(); i++)
    {
        cout << (*spa)[i] << " ";
    }
    cout << endl;
    cout << endl;

    pbtn = bt.find(6);
    bt.insert(11, pbtn, BTNP_LEFT);

    s32 a[] = {8, 9, 10, 11, 7};

    cout << "----------------------------------" << endl;
    for(u32 i = 0; i < (sizeof(a)/sizeof(a[0])); i++)
    {
        TreeNode<s32> *node = bt.find(a[i]);

        while(node)
        {
            cout << node->value << " ";

            node = node->parent;
        }

        cout << endl;
    }
    cout << endl;

    cout << "---compare bt(after add a new node) with bt_clone---" << endl;
    cout << "bt == *bt_clone : " << (bt == *bt_clone) << endl;
    cout << endl;

    SharedPointer< Tree<s32> > sp = bt.remove(3);

    cout << "----------------------------------" << endl;
    for(u32 i = 0; i < (sizeof(a)/sizeof(a[0])); i++)
    {
        TreeNode<s32> *node = bt.find(a[i]);

        while(node)
        {
            cout << node->value << " ";

            node = node->parent;
        }

        cout << endl;
    }
    cout << endl;

    cout << "----------------------------------" << endl;
    for(u32 i = 0; i < (sizeof(a)/sizeof(a[0])); i++)
    {
        TreeNode<s32> *node = sp->find(a[i]);

        while(node)
        {
            cout << node->value << " ";

            node = node->parent;
        }

        cout << endl;
    }
    cout << endl;

    BTree<s32> bt2;

    bt2.insert(0, NULL);

    pbtn = bt2.find(0);
    bt2.insert(6, pbtn);
    bt2.insert(2, pbtn);

    pbtn = bt2.find(2);
    bt2.insert(7, pbtn);
    bt2.insert(8, pbtn);

    s32 a2[] = {6, 7, 8};

    cout << "---------------create bt2-----------------" << endl;
    for(u32 i = 0; i < (sizeof(a2)/sizeof(a2[0])); i++)
    {
        TreeNode<s32> *node = bt2.find(a2[i]);

        while(node)
        {
            cout << node->value << " ";

            node = node->parent;
        }

        cout << endl;
    }
    cout << endl;

    cout << "---bt_clone add bt2, then preorder---" << endl;
    SharedPointer< BTree<s32> > bt_add = bt_clone->add(bt2);
    spa = bt_add->traversal(BTT_PRE_ORDER);
    for(s32 i = 0; i < (*spa).length(); i++)
    {
        cout << (*spa)[i] << " ";
    }
    cout << endl;

    s32 a_add[] = {8, 9, 10, 13, 15};

    for(u32 i = 0; i < (sizeof(a_add)/sizeof(a_add[0])); i++)
    {
        TreeNode<s32> *node = bt_add->find(a_add[i]);

        while(node)
        {
            cout << node->value << " ";

            node = node->parent;
        }

        cout << endl;
    }
    cout << endl;

    return 0;
}

