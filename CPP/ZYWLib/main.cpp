#include <iostream>
#include "LinkList.h"
#include "SmartPointer.h"
#include "SharedPointer.h"

using namespace std;
using namespace ZYWLib;

class Test
{
public:
    ZYW_INT32 val;

public:
    Test()
    {
        val = 0;
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

#if 0
    SmartPointer<Test> t = new Test();
    SmartPointer<Test> ts;

    ts = t;
#endif

#if 1
#if 0
    SharedPointer<Test> sp = new Test();
    SharedPointer<Test> sps = sp;
    SharedPointer<Test> spt;

    spt = sps;

    spt->val = 100;

    cout << sp->val << endl;
    cout << sps->val << endl;
    cout << spt->val << endl;

    cout << (sp==sps) << endl;

    sps.clear();

    cout << (sp==sps) << endl;

    sp.clear();
    spt.clear();
#else
    const SharedPointer<Test> sp = new Test();

    //sp->val = 100;  /* 编译出错，为什么？因为const修饰的指针变量(const在最前)当然是只读的啦。 */
#endif
#endif

    return 0;
}

