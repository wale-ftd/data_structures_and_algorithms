#include "Standard.h"

extern s32 list_graph_test(s32 argc, s8** argv);
extern s32 graph_traversal_test(s32 argc, s8** argv);

s32 main(s32 argc, s8** argv)
{
    //list_graph_test(argc, argv);

    graph_traversal_test(argc, argv);

    return 0;
}

