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

    /* ���Զ�������Test���̳�Objectʱ������������==��������
       ����뱨����Ȼ�̳���Object����������==����������
       ObjectĬ�ϵ�==��������������ܲ���ȷ���������ﻹ��Ҫ����һ
       ��==��������
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

