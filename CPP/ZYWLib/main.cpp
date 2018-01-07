#include <iostream>
#include "LinkList.h"
#include "SmartPointer.h"

USING_NAMESPACE(std);
USING_NAMESPACE(ZYWLib);

class Test
{
public:
    Test()
    {
        cout << "Test()" << endl;
    }

    ~Test()
    {
        cout << "~Test()" << endl;
    }
};

ZYW_INT32 main(ZYW_INT32 argc, ZYW_INT8** argv)
{
#if 0
    LinkList<ZYW_INT32> list;

    for(int i = 0; i < 5; i++)
        list.insert(i);

    for(list.move(0); !list.end(); list.next())
        cout << list.current() << endl;
#endif

    SmartPointer<Test> t = new Test();
    SmartPointer<Test> ts;

    ts = t;

    return 0;
}

