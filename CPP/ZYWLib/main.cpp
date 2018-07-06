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

    pbtn = bt.find(6);
    bt.insert(11, pbtn, BTNP_LEFT);

    s32 a[] = {8, 9, 10, 11, 7};

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

    return 0;
}

