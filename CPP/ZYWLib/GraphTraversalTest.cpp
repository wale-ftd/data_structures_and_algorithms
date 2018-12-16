#include <iostream>
#include "MatrixGraph.h"

using namespace std;
using namespace DSaALib;

#define MATRIX_GRAPH_NODE_NUM (9)

template<typename V, typename E>
void DFS_Recursive(Graph<V, E>& g, s32 v, Array<bool>& visited)
{
    if((0<=v) && (v<g.vCount()))
    {
        cout << v << " ";

        visited[v] = true;

        SharedPointer< Array<s32> > adj = g.getAdjacent(v);

        for(s32 i = 0; i < adj->length(); i++)
        {
            if(!visited[(*adj)[i]])
            {
                DFS_Recursive(g, (*adj)[i], visited);
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Index v is invalid ...");
    }
}

template<typename V, typename E>
void DFS_Recursive(Graph<V, E>& g, s32 v)
{
    DynamicArray<bool> visited(g.vCount());

    for(s32 i = 0; i < visited.length(); i++)
    {
        visited[i] = false;
    }

    DFS_Recursive(g, v, visited);

    cout << endl;
}

s32 graph_traversal_test(s32 argc, s8** argv)
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

    cout << "---test BFS---" << endl;

    SharedPointer< Array<s32> > spa = mg.BFS(0);

    for(s32 i = 0; i < spa->length(); i++)
    {
        cout << (*spa)[i] << " ";
    }
    cout << endl;

    cout << "---test DFS---" << endl;

    spa = mg.DFS(0);

    for(s32 i = 0; i < spa->length(); i++)
    {
        cout << (*spa)[i] << " ";
    }
    cout << endl;

    cout << "---test DFS_Recursive---" << endl;

    DFS_Recursive(mg, 0);

    return 0;
}
