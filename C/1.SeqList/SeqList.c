#include <malloc.h>
#include "SeqList.h"
#include <stdio.h>

typedef struct _seq_list_type {
    //void *p_node;   /* �������У����붼�����ˡ����ڲ��롢ɾ������ʱ����p_list_tmp->p_node[pos] = p_node�����ĸ�ֵ��void�����Խ��и�ֵ������Ϊ���ô����ݽṹ���������������͵�����Ԫ���ϣ�������p_node���ŵ��ǵ�ַ */
    unsigned long *p_node;   /* Ϊ���ô����ݽṹ���������������͵�����Ԫ���ϣ�������p_node���ŵ��ǵ�ַ */
    int capacity;   /* ˳������� */
    int length;     /* ˳���ǰ���� */
} SEQ_LIST_TYPE;

SeqList* SeqListCreate(int capacity)   /* O(1) */
{
    SEQ_LIST_TYPE *ret = NULL;
    
    if(0 > capacity)
        return ret;

/*
                                        0   ~   capacity-1
	+----------+----------+-----------+----------------------------------------------------------+
	| capacity |  length  |   p_node  |                 sizeof(void *) * capacity                |
	+----------+----------+-----------+----------------------------------------------------------+
	|<-------  ret  ----------------->|
	^                                 ^ 
	|                                 |
   ret                              ret+1
*/    
    ret = (SEQ_LIST_TYPE *)malloc(sizeof(SEQ_LIST_TYPE) + capacity * sizeof(unsigned long *));

    if(ret)
    {
        ret->capacity = capacity;
        ret->length = 0;
        ret->p_node = (unsigned long *)(ret + 1);    /* �ص����  SEQ_LIST_TYPE�е�p_node���ŵ�����������������׵�ַ��ָ�����ݴ�ŵĿ�ʼλ�� */ 
    }

    return (SeqList *)ret;
}

#if 0
void SeqListDestroy(SeqList *p_list)   /* O(1) */
{
    printf("&p_list = %p.\n", &p_list);      // 0xbfbe6820 ��ջ��
    printf("p_list = %p.\n", p_list);       // 0x83ec008

    if(p_list)
    {
        free(p_list);
        p_list = NULL;  /* ������䲢ûʲô�ã�����û�У�ֻ�ܸı�ջ��p_list��ֵ�����ܸı���ô˺������Ĳ���seq_list��ֵ */
    }
}
#else
void SeqListDestroy(SeqList **pp_list)   /* O(1) */
{
    printf("&pp_list = %p.\n", &pp_list);     // 0xbfbe6820
    printf("pp_list = %p.\n", pp_list);       // 0xbfbe6830
    printf("*pp_list = %p.\n", *pp_list);     // 0x83ec008

    if(*pp_list)
    {
        free(*pp_list);
        *pp_list = NULL; /* ���Ըı���ô˺������Ĳ���seq_list��ֵ */
    }
}
#endif

void SeqListClear(SeqList *p_list) /* O(1) */
{
    SEQ_LIST_TYPE *p_list_tmp = (SEQ_LIST_TYPE *)p_list;
    
    if(p_list_tmp)
        p_list_tmp->length = 0;
}

int SeqListCapacity(SeqList *p_list)   /* O(1) */
{
    int ret = -1;
    SEQ_LIST_TYPE *list_tmp_ptr = (SEQ_LIST_TYPE *)p_list;

    if(list_tmp_ptr)
        ret = list_tmp_ptr->capacity;

    return ret;
}
int SeqListLength(SeqList *p_list) /* O(1) */
{
    int ret = -1;
    SEQ_LIST_TYPE *list_tmp_ptr = (SEQ_LIST_TYPE *)p_list;

    if(list_tmp_ptr)
        ret = list_tmp_ptr->length;

    return ret;
}

int SeqListInsert(SeqList *p_list, SeqListNode *p_node, int pos)  /* O(n) */
{
    int ret = -1;
    SEQ_LIST_TYPE *p_list_tmp = (SEQ_LIST_TYPE *)p_list;
    int i = 0;

    if(p_list_tmp && p_node && (0<=pos) && (p_list_tmp->capacity>=(p_list_tmp->length+1)))
    {
        /* ����posֵ */
        if(pos >= p_list_tmp->length)
            pos = p_list_tmp->length;   /* Ϊʲô����length+1?��Ϊ�涨��һ��Ԫ�ص��±���0������0��ʼ�� */

        /* �ڳ��ռ� */
        for(i = p_list_tmp->length-1; pos <= i; i--)
            p_list_tmp->p_node[i+1] = p_list_tmp->p_node[i];
//        for(i = list_tmp_ptr->length; pos < i; i--)
//            list_tmp_ptr->node_ptr[i] = list_tmp_ptr->node_ptr[i-1];

        /* ���� */
        p_list_tmp->p_node[pos] = (unsigned long)p_node;
//        list_tmp_ptr->node_ptr[i] = (SEQ_LIST_NODE_TYPE)node_ptr;
        
        p_list_tmp->length++;
        
        ret = 0;
    }

    return ret;
}

SeqListNode* SeqListGet(SeqList *p_list, int pos) /* O(1) */
{
    SEQ_LIST_TYPE *p_list_tmp = (SEQ_LIST_TYPE *)p_list;
    SeqListNode *ret = NULL;

    if(p_list_tmp && (0<=pos) && (p_list_tmp->length>pos))
    {
        ret = (SeqListNode *)p_list_tmp->p_node[pos];
    }

    return ret;
}

SeqListNode* SeqListDelete(SeqList *p_list, int pos)  /* O(n) */
{
    SEQ_LIST_TYPE *p_list_tmp = (SEQ_LIST_TYPE *)p_list;
    SeqListNode *ret = NULL;
    int i = 0;

    /* ����һ: */
    #if 0
    if(p_list_tmp && (0<=pos) && (p_list_tmp->length>pos))
    {
        ret = (SeqListNode *)p_list_tmp->p_node[pos];

        for(i = (pos+1); i<p_list_tmp->length; i++)
            p_list_tmp->p_node[i-1] = p_list_tmp->p_node[i];

        p_list_tmp->length--;
    }
    else
    {
        printf("illegal parameter.\n");
    }
    /* ������: ֱ�ӵ���SeqList_Get()����Ϊ��SeqList_Get()�����˺Ϸ��Եļ�⣬�����������ʡ�ԺϷ��Եļ�� */
    #else
    ret = SeqListGet(p_list, pos);
    if(ret)
    {
        for(i = (pos+1); i<p_list_tmp->length; i++)
            p_list_tmp->p_node[i-1] = p_list_tmp->p_node[i];

        p_list_tmp->length--;
    }
    
    #endif

    return ret;
}

