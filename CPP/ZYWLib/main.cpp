#include <iostream>
#include "MatrixGraph.h"

using namespace std;
using namespace DSaALib;

s32 main(s32 argc, s8** argv)
{
    MatrixGraph<3, s32, s32> mg;

    mg.setEdge(0, 1, 1);
    mg.setEdge(1, 0, 2);
    mg.setEdge(1, 2, 3);

    cout << "vCount: " << mg.vCount() << endl;
    cout << "eCount: " << mg.eCount() << endl;
    cout << "ID(1): " << mg.ID(1) << endl;
    cout << "OD(1): " << mg.OD(1) << endl;
    cout << "TD(1): " << mg.TD(1) << endl;

    cout << "W(0, 1): " << mg.getEdge(0, 1) << endl;
    cout << "W(1, 0): " << mg.getEdge(1, 0) << endl;
    cout << "W(1, 2): " << mg.getEdge(1, 2) << endl;

    //SharedPointer< Array<s32> > aj = mg.getAdjacent(1);
    //SharedPointer< Array<s32> > aj = mg.getAdjacent(0);
    SharedPointer< Array<s32> > aj = mg.getAdjacent(2);
    for(s32 i = 0; i < aj->length(); i++)
    {
        cout << (*aj)[i] << " ";
    }
    cout << endl;

    cout << "Delete Edge: " << endl;
    mg.removeEdge(0, 1);
    cout << "eCount: " << mg.eCount() << endl;

    mg.setVertex(0, 100);
    cout << "V(0): " << mg.getVertex(0) << endl;

    cout << "W(0, 1): " << mg.getEdge(0, 1) << endl;

    return 0;
}

