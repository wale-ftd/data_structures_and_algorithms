#include <iostream>
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
