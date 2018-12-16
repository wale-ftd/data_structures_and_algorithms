#include <iostream>
#include "MatrixGraph.h"
#include "ListGraph.h"

using namespace std;
using namespace DSaALib;

s32 list_graph_test(s32 argc, s8** argv)
{
//    ListGraph<s8, s32> lg(4);

//    lg.setVertex(0, 'A');
//    lg.setVertex(1, 'B');
//    lg.setVertex(2, 'C');
//    lg.setVertex(3, 'D');

    ListGraph<s8, s32> lg;

    lg.addVertex('A');
    lg.addVertex('B');
    lg.addVertex('C');
    lg.addVertex('D');

    //lg.removeVertex();

    for(s32 i = 0; i < lg.vCount(); i++)
    {
        cout << i << " : " << lg.getVertex(i) << endl;
    }

    lg.setEdge(0, 1, 5);
    lg.setEdge(0, 3, 6);
    lg.setEdge(1, 2, 8);
    lg.setEdge(2, 3, 2);
    lg.setEdge(3, 1, 9);

    cout << "W(0, 1) : " << lg.getEdge(0, 1) << endl;
    cout << "W(0, 3) : " << lg.getEdge(0, 3) << endl;
    cout << "W(1, 2) : " << lg.getEdge(1, 2) << endl;
    cout << "W(2, 3) : " << lg.getEdge(2, 3) << endl;
    cout << "W(3, 1) : " << lg.getEdge(3, 1) << endl;

    cout << "eCount : " << lg.eCount() << endl;

    //lg.removeEdge(3, 1);

    //cout << "W(3, 1) : " << lg.getEdge(3, 1) << endl;

    cout << "eCount : " << lg.eCount() << endl;

    s32 vertex = 0;
    SharedPointer< Array<s32> > aj = lg.getAdjacent(vertex);
    cout << "adjacent of vertex " << vertex << " is : ";
    for(s32 i = 0; i < aj->length(); i++)
    {
         cout << (*aj)[i] << " ";
    }
    cout << endl;

    vertex = 1;
    cout << "ID(" << vertex << ") = " << lg.ID(vertex) << endl;
    cout << "OD(" << vertex << ") = " << lg.OD(vertex) << endl;
    cout << "TD(" << vertex << ") = " << lg.ID(vertex) + lg.OD(vertex) << endl;

    lg.removeVertex();
    cout << "vCount : " << lg.vCount() << endl;
    cout << "eCount : " << lg.eCount() << endl;
    cout << "W(0, 1) : " << lg.getEdge(0, 1) << endl;
    cout << "W(1, 2) : " << lg.getEdge(1, 2) << endl;
    //cout << "W(2, 3) : " << lg.getEdge(2, 3) << endl;

    return 0;
}

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
