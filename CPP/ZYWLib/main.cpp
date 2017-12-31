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

    /* 遍历链表。理论上O(n)即可完成，但这里却是O(n^2)，很奇怪吧。 */
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

