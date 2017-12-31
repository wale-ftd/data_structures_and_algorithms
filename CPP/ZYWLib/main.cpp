#include <iostream>
#include "LinkList.h"

USING_NAMESPACE(std);
USING_NAMESPACE(ZYWLib);

ZYW_INT32 main(ZYW_INT32 argc, ZYW_INT8** argv)
{
    LinkList<ZYW_INT32> list;

    for(ZYW_INT32 i = 0; i < 5; i++)    /* O(n) */
    {
        list.insert(0, i);
    }

    /* ��������������O(n)������ɣ�������ȴ��O(n^2)������ְɡ� */
    for(ZYW_INT32 i = 0; i < list.length(); i++)    /* O(n^2) */
    {
        cout << list.get(i) << endl;
    }

    cout << endl;

    for(list.move(0); !list.end(); list.next()) /* O(n) */
    {
        cout << list.current() << endl;
    }

    cout << endl;

    for(list.move(0, 2); !list.end(); list.next()) /* O(n) */
    {
        cout << list.current() << endl;
    }

    cout << endl;

    for(list.move(0, 3); !list.end(); list.next()) /* O(n) */
    {
        cout << list.current() << endl;
    }

    cout << endl;

    for(list.move(0, 10); !list.end(); list.next()) /* O(n) */
    {
        cout << list.current() << endl;
    }

    return 0;
}

