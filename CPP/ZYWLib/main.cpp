#include <iostream>
#include "LinkList.h"

USING_NAMESPACE(std);
USING_NAMESPACE(ZYWLib);

class Test: public Object
{
private:
    ZYW_INT32 i;

public:
    Test(ZYW_INT32 v = 0)
    {
        i = v;
    }

    /* 当自定义类型Test不继承Object时，并且又重载==操作符，
       会编译报错。虽然继承了Object，但不重载==操作符，用
       Object默认的==操作符，结果可能不正确，所以这里还是要重载一
       下==操作符。
     */
    ZYW_BOOL operator ==(const Test& obj)
    {
        return (i == obj.i);
    }
};

ZYW_INT32 main(ZYW_INT32 argc, ZYW_INT8** argv)
{
    LinkList<ZYW_INT32> list;

    for(ZYW_INT32 i = 0; i < 5; i++)
    {
        list.insert(0, i);
    }

    cout << list.find(3) << endl;
    cout << list.find(7) << endl;

    LinkList<Test> t_list;
    Test t1(1);
    Test t2(2);
    Test t3(3);
    Test t4(4);

    t_list.insert(t1);
    t_list.insert(t2);
    t_list.insert(t3);

    cout << t_list.find(t2) << endl;
    cout << t_list.find(t4) << endl;

    return 0;
}

