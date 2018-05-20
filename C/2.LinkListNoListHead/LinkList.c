#include <malloc.h>
#include <stdio.h>
#include "LinkList.h"


/* 创建单向链表 */
LINK_LIST *LinkListCreate(void)     /* O(1) */
{
    return NULL;
}

void LinkListDestroy(LINK_LIST **pp_list)   /* O(1) */
{
    if(*pp_list) {
        *pp_list = NULL;    /* 改变头指针的指向 */
    }
}

void LinkListClear(LINK_LIST **pp_list)   /* O(1) */
{
    if(*pp_list) {
        *pp_list = NULL;    /* 改变头指针的指向 */
    }
}

int LinkListLength(LINK_LIST *p_list)   /* O(n) */
{
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list;
    int i = 0;
    
    for(i = 0; cur; i++, cur=cur->next);
    
    return i;
}

int LinkListInsert(LINK_LIST **pp_list, LINK_LIST *p_list, LINK_LIST_NODE *p_node, int pos)  /* O(n)。最好是头插O(1)，最坏是尾插O(n) */
{
    int ret = -1;
    int i;
    /* 使当前节点指针指向头节点 */
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list;

    if((NULL==p_node) || (0 > pos))
        return ret;

    if((!cur) || (0==pos))
    {
        /* 插入 */
        p_node->next = cur;
        *pp_list = p_node;  /* 改变头指针的指向 */
    }
    else
    {
        /* 找到要插入位置的前一个节点，并让cur指向它 */
        for(i = 0; (i<(pos-1)) && cur->next; i++, cur=cur->next);
        
        /* 插入 */
        p_node->next = cur->next;
        cur->next = p_node;
    }
    
    ret = 0;

    return ret;
}

LINK_LIST_NODE *LinkListGet(LINK_LIST *p_list, int pos) /* O(n)。最好是获取第一个节点O(1)，最坏是获取最后一个节点O(n) */
{
    LINK_LIST_NODE *ret = NULL;
    int i;
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list;

    if(0 > pos)
        return ret;

    if((!cur) || (0==pos))
    {
        ret = cur;
    }
    else
    {
        /* 找到要获取节点的前一个节点 */
        for(i = 0; (i<(pos-1)) && cur->next; i++, cur=cur->next);    // 修改前

        if(i != (pos-1))
        {
            printf("the parameter of pos is ilegal.\n");
        }
        
        ret = cur->next;
    }
    
    return ret;
}

LINK_LIST_NODE *LinkListDelete(LINK_LIST **pp_list, LINK_LIST *p_list, int pos)  /* O(n)。最好是删除第一个节点O(1)，最坏是删除最后一个节点O(n) */
{
    LINK_LIST_NODE *ret = NULL;
    int i;
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list;

    if(0 > pos)
        return ret;

    if((!cur) || (0==pos))
    {
        ret = cur;

        *pp_list = cur->next;   /* 改变头指针的指向 */
    }
    else
    {
        /* 找到要删除节点的前一个节点 */
        for(i = 0; (i<(pos-1)) && cur->next; i++, cur=cur->next);    // 修改前

        if(i != (pos-1))
        {
            printf("the parameter of pos is ilegal.\n");
            ret = cur->next;
        }
        else
        {
            ret = cur->next;
            cur->next = ret->next;
        }
        
    }

    return ret;
}


