#include <iostream>
#include <string.h>
#include "BTree.h"


using namespace std;
using namespace DSaALib;

s32 main(s32 argc, s8** argv)
{
    BTree<s32> bt;
    BTreeNode<s32> btn;

    bt.find(1);
    bt.find(&btn);

    return 0;
}

