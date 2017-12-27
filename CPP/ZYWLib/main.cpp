#include <iostream>
#include "DynamicArray.h"

USING_NAMESPACE(std);
USING_NAMESPACE(ZYWLib);

ZYW_INT32 main(ZYW_INT32 argc, ZYW_INT8** argv)
{
    DynamicArray<ZYW_INT32> s1(5);

    for(ZYW_INT32 i = 0; i < s1.length(); i++)
    {
        s1[i] = i * i;
    }

    for(ZYW_INT32 i = 0; i < s1.length(); i++)
    {
        cout << s1[i] << endl;
    }

    DynamicArray<ZYW_INT32> s2(10);

    s2 = s1;

    for(ZYW_INT32 i = 0; i < s2.length(); i++)
    {
        cout << s2[i] << endl;
    }

    s2.resize(8);

    for(ZYW_INT32 i = 0; i < s2.length(); i++)
    {
        cout << s2[i] << endl;
    }

    s2.resize(3);

    for(ZYW_INT32 i = 0; i < s2.length(); i++)
    {
        cout << s2[i] << endl;
    }

    s2[4] = 100;

    return 0;
}

