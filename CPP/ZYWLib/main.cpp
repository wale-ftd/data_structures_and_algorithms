#include <iostream>
#include "LinkList.h"

USING_NAMESPACE(std);
USING_NAMESPACE(ZYWLib);

class Test
{
public:
    Test()
    {
        throw 0;
    }
};

ZYW_INT32 main(ZYW_INT32 argc, ZYW_INT8** argv)
{
#if 1
    /* 用匿名类重新定义头节点，避开了一个互扯的问题(明明是使用者制造的问题而被抱怨是ZYWLib的问题)，使得ZYWLib更健壮。 */
    LinkList<Test> list;

    //Test t; /* 暴露问题 */
    //list.insert(t);

    cout << "Hello wale!!!" << endl;
#else
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
#endif

    return 0;
}

