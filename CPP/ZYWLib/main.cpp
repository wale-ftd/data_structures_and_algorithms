#include <iostream>
#include "DynamicArray.h"

USING_NAMESPACE(std);
USING_NAMESPACE(ZYWLib);

ZYW_INT32 main(ZYW_INT32 argc, ZYW_INT8** argv)
{
    DynamicArray< DynamicArray<ZYW_INT32> > d;

    d.resize(3);

    for(ZYW_INT32 i = 0; i < d.length(); i++)
    {
        //d[i].resize(3);
        d[i].resize(i + 1);
    }


    for(ZYW_INT32 i = 0; i < d.length(); i++)
    {
        for(ZYW_INT32 j = 0; j < d[i].length(); j++)
        {
            d[i][j] = i + j;
        }
    }

    for(ZYW_INT32 i = 0; i < d.length(); i++)
    {
        for(ZYW_INT32 j = 0; j < d[i].length(); j++)
        {
            cout << d[i][j] << " ";
        }

        cout << endl;
    }

    return 0;
}

