#include <iostream>
#include "GTree.h"


using namespace std;
using namespace ZYWLib;

ZYW_INT32 main(ZYW_INT32 argc, ZYW_INT8** argv)
{
    GTree<ZYW_INT32> t;
    GTreeNode<ZYW_INT32> tn;

    t.find(0);
    t.find(&tn);

    return 0;
}

