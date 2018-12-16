#include <iostream>
#include "MatrixGraph.h"

using namespace std;
using namespace DSaALib;

#define MATRIX_GRAPH_NODE_NUM (9)

s32 graph_BFS_test(s32 argc, s8** argv)
{
    MatrixGraph<MATRIX_GRAPH_NODE_NUM, s8, s32> mg;
    const char *VD = "ABEDCGFHI";

    for(s32 i = 0; i < MATRIX_GRAPH_NODE_NUM; i++)
    {
        mg.setVertex(0, VD[i]);
    }

    mg.setEdge(0, 1, 0);
    mg.setEdge(1, 0, 0);

    mg.setEdge(0, 3, 0);
    mg.setEdge(3, 0, 0);

    mg.setEdge(0, 4, 0);
    mg.setEdge(4, 0, 0);

    mg.setEdge(1, 2, 0);
    mg.setEdge(2, 1, 0);

    mg.setEdge(1, 4, 0);
    mg.setEdge(4, 1, 0);

    mg.setEdge(2, 5, 0);
    mg.setEdge(5, 2, 0);

    mg.setEdge(3, 6, 0);
    mg.setEdge(6, 3, 0);

    mg.setEdge(4, 6, 0);
    mg.setEdge(6, 4, 0);

    mg.setEdge(6, 7, 0);
    mg.setEdge(7, 6, 0);

    mg.setEdge(7, 8, 0);
    mg.setEdge(8, 7, 0);

    SharedPointer< Array<s32> > spa = mg.BFS(0);

    for(s32 i = 0; i < spa->length(); i++)
    {
        cout << (*spa)[i] << " ";
    }
    cout << endl;

    return 0;
}
