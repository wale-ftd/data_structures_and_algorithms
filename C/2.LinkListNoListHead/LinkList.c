#include <malloc.h>
#include <stdio.h>
#include "LinkList.h"


/* ������������ */
LINK_LIST *LinkListCreate(void)     /* O(1) */
{
    return NULL;
}

void LinkListDestroy(LINK_LIST **pp_list)   /* O(1) */
{
    if(*pp_list) {
        *pp_list = NULL;    /* �ı�ͷָ���ָ�� */
    }
}

void LinkListClear(LINK_LIST **pp_list)   /* O(1) */
{
    if(*pp_list) {
        *pp_list = NULL;    /* �ı�ͷָ���ָ�� */
    }
}

int LinkListLength(LINK_LIST *p_list)   /* O(n) */
{
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list;
    int i = 0;
    
    for(i = 0; cur; i++, cur=cur->next);
    
    return i;
}

int LinkListInsert(LINK_LIST **pp_list, LINK_LIST *p_list, LINK_LIST_NODE *p_node, int pos)  /* O(n)�������ͷ��O(1)�����β��O(n) */
{
    int ret = -1;
    int i;
    /* ʹ��ǰ�ڵ�ָ��ָ��ͷ�ڵ� */
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list;

    if((NULL==p_node) || (0 > pos))
        return ret;

    if((!cur) || (0==pos))
    {
        /* ���� */
        p_node->next = cur;
        *pp_list = p_node;  /* �ı�ͷָ���ָ�� */
    }
    else
    {
        /* �ҵ�Ҫ����λ�õ�ǰһ���ڵ㣬����curָ���� */
        for(i = 0; (i<(pos-1)) && cur->next; i++, cur=cur->next);
        
        /* ���� */
        p_node->next = cur->next;
        cur->next = p_node;
    }
    
    ret = 0;

    return ret;
}

LINK_LIST_NODE *LinkListGet(LINK_LIST *p_list, int pos) /* O(n)������ǻ�ȡ��һ���ڵ�O(1)����ǻ�ȡ���һ���ڵ�O(n) */
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
        /* �ҵ�Ҫ��ȡ�ڵ��ǰһ���ڵ� */
        for(i = 0; (i<(pos-1)) && cur->next; i++, cur=cur->next);    // �޸�ǰ

        if(i != (pos-1))
        {
            printf("the parameter of pos is ilegal.\n");
        }
        
        ret = cur->next;
    }
    
    return ret;
}

LINK_LIST_NODE *LinkListDelete(LINK_LIST **pp_list, LINK_LIST *p_list, int pos)  /* O(n)�������ɾ����һ���ڵ�O(1)�����ɾ�����һ���ڵ�O(n) */
{
    LINK_LIST_NODE *ret = NULL;
    int i;
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list;

    if(0 > pos)
        return ret;

    if((!cur) || (0==pos))
    {
        ret = cur;

        *pp_list = cur->next;   /* �ı�ͷָ���ָ�� */
    }
    else
    {
        /* �ҵ�Ҫɾ���ڵ��ǰһ���ڵ� */
        for(i = 0; (i<(pos-1)) && cur->next; i++, cur=cur->next);    // �޸�ǰ

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


