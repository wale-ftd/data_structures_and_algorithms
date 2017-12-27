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
    /* �����������¶���ͷ�ڵ㣬�ܿ���һ������������(������ʹ������������������Թ��ZYWLib������)��ʹ��ZYWLib����׳�� */
    LinkList<Test> list;

    //Test t; /* ��¶���� */
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

