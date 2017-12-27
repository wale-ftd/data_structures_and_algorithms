#include <iostream>
#include "LinkList.h"

USING_NAMESPACE(std);
USING_NAMESPACE(ZYWLib);

ZYW_INT32 main(ZYW_INT32 argc, ZYW_INT8** argv)
{
    LinkList<ZYW_INT32> list;

    for(ZYW_INT32 i = 0; i < 5; i++)
    {
        list.insert(0, i);
        list.set(0, i*i);
    }

    for(ZYW_INT32 i = 0; i < list.length(); i++)
    {
        cout << list.get(i) << endl;
    }

    list.remove(2);

    for(ZYW_INT32 i = 0; i < list.length(); i++)
    {
        cout << list.get(i) << endl;
    }

    list.clear();

    for(ZYW_INT32 i = 0; i < list.length(); i++)
    {
        cout << list.get(i) << endl;
    }

    return 0;
}

