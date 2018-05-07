#include <stdio.h>
#include "LinkList.h"


struct Value
{
    LINK_LIST_NODE header;
    int v;
};


int main(int argc, char **argv)
{
    LINK_LIST *link_list = NULL;
    int index = 0;
    struct Value a;
    struct Value b;
    struct Value c;
    struct Value d;
    struct Value e;
    struct Value f;
    struct Value g;

    a.v = 5;
    b.v = 4;
    c.v = 3;
    d.v = 2;
    e.v = 1;
    f.v = 0;
    g.v = 6;

    printf("/*-----------------create-------------------*/\n");
    link_list = LinkListCreate();
    printf("length = %d\n", LinkListLength(link_list));
    printf("\n");

    printf("/*-----------------add-------------------*/\n");
    LinkListInsertHead(&link_list, link_list, (LINK_LIST_NODE *)&a);
    LinkListInsertHead(&link_list, link_list, (LINK_LIST_NODE *)&b);
    LinkListInsertHead(&link_list, link_list, (LINK_LIST_NODE *)&c);
    LinkListInsertHead(&link_list, link_list, (LINK_LIST_NODE *)&d);
    LinkListInsertHead(&link_list, link_list, (LINK_LIST_NODE *)&e);
    LinkListInsertHead(&link_list, link_list, (LINK_LIST_NODE *)&f);
    LinkListInsert(&link_list, link_list, (LINK_LIST_NODE *)&g, 3);
    printf("length = %d\n", LinkListLength(link_list));
    for(index = 0; index < LinkListLength(link_list); index++)
        printf("[%d] = %d\n", index, ((struct Value *)LinkListGet(link_list, index))->v);
    printf("\n");

    printf("/*-----------------detele-------------------*/\n");
    while(3 < LinkListLength(link_list))
        printf("del = %d\n", ((struct Value *)LinkListDelete(&link_list, link_list, 0))->v);  /* ͷɾ */
        //printf("del = %d\n", ((struct Value *)LinkListDelete(&link_list, link_list, LinkListLength(link_list)-1))->v);  /* βɾ */
        //printf("del = %d\n", ((struct Value *)LinkListDelete(&link_list, link_list, LinkListLength(link_list)))->v); /* ����posֵ���ܴ���length��ֵ */
    printf("del = %d\n", ((struct Value *)LinkListDelete(&link_list, link_list, 1))->v);
    printf("\n");

    printf("/*-----------------desplay remains-------------------*/\n");
    printf("length = %d\n", LinkListLength(link_list));
    for(index = 0; index < LinkListLength(link_list); index++)
        printf("[%d] = %d\n", index, ((struct Value *)LinkListGet(link_list, index))->v);
    printf("\n");

    printf("/*-----------------destroy-------------------*/\n");
#if 0
    printf("&link_list = %p.\n", &link_list);                     // 0xbfbe6830
    printf("link_list = %p.\n", link_list);                       // 0x83ec008
    LinkListDestroy(link_list);  /* Ϊ����link_listָ����ڴ��ͷź�link_list = NULL�������д��������ʵ�����ǵ��뷨 */
    printf("&link_list = %p.\n", &link_list);                     // 0xbfbe6830
    printf("link_list = %p.\n", link_list);                       // 0x83ec008, ��ΪNULL
    printf("length = %d\n", LinkListLength(link_list));           // 2
    printf("\n");
#else
    printf("&link_list = %p.\n", &link_list);                     // 0xbfbe6830
    printf("link_list = %p.\n", link_list);                       // 0x83ec008
    LinkListDestroy(&link_list);  /* Ϊ����link_listָ����ڴ��ͷź�link_list = NULL���ɹ� */
    printf("&link_list = %p.\n", &link_list);                     // 0xbfbe6830
    printf("link_list = %p.\n", link_list);                       // NULL
    printf("length = %d\n", LinkListLength(link_list));           // -1
    printf("\n");
#endif

    return 0;
}

