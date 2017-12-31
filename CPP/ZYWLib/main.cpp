#include <iostream>
#include "StaticLinkList.h"

USING_NAMESPACE(std);
USING_NAMESPACE(ZYWLib);

ZYW_INT32 main(ZYW_INT32 argc, ZYW_INT8** argv)
{
    StaticLinkList<ZYW_INT32, 5> slist;

    for(ZYW_INT32 i = 0; i < 5; i++)
    {
        slist.insert(0, i);
    }

    for(slist.move(0); !slist.end(); slist.next())
    {
        cout << slist.current() << endl;
    }

    cout << endl;

    try
    {
        slist.insert(6);
    }
    catch(const Exception& e)
    {
        cout << e.message() << endl;
    }

    for(slist.move(0); !slist.end(); slist.next())
    {
        cout << slist.current() << endl;
    }

    return 0;
}

