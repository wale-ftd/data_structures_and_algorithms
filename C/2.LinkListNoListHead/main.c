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
        printf("del = %d\n", ((struct Value *)LinkListDelete(&link_list, link_list, 0))->v);  /* 头删 */
        //printf("del = %d\n", ((struct Value *)LinkListDelete(&link_list, link_list, LinkListLength(link_list)-1))->v);  /* 尾删 */
        //printf("del = %d\n", ((struct Value *)LinkListDelete(&link_list, link_list, LinkListLength(link_list)))->v); /* 出错，pos值不能大于length的值 */
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
    LinkListDestroy(link_list);  /* 为了让link_list指向的内存释放后，link_list = NULL，但这个写法并不能实现我们的想法 */
    printf("&link_list = %p.\n", &link_list);                     // 0xbfbe6830
    printf("link_list = %p.\n", link_list);                       // 0x83ec008, 不为NULL
    printf("length = %d\n", LinkListLength(link_list));           // 2
    printf("\n");
#else
    printf("&link_list = %p.\n", &link_list);                     // 0xbfbe6830
    printf("link_list = %p.\n", link_list);                       // 0x83ec008
    LinkListDestroy(&link_list);  /* 为了让link_list指向的内存释放后，link_list = NULL，成功 */
    printf("&link_list = %p.\n", &link_list);                     // 0xbfbe6830
    printf("link_list = %p.\n", link_list);                       // NULL
    printf("length = %d\n", LinkListLength(link_list));           // -1
    printf("\n");
#endif

    return 0;
}

