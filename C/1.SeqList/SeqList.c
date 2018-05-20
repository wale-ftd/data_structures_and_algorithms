#include <malloc.h>
#include "SeqList.h"
#include <stdio.h>

typedef struct _seq_list_type {
    //void *p_node;   /* 这样不行，编译都过不了。因在插入、删除操作时会有p_list_tmp->p_node[pos] = p_node这样的赋值，void不可以进行赋值操作。为了让此数据结构可以用在任意类型的数据元素上，所以在p_node里存放的是地址 */
    unsigned long *p_node;   /* 为了让此数据结构可以用在任意类型的数据元素上，所以在p_node里存放的是地址 */
    int capacity;   /* 顺序表容量 */
    int length;     /* 顺序表当前长度 */
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
        ret->p_node = (unsigned long *)(ret + 1);    /* 重点理解  SEQ_LIST_TYPE中的p_node域存放的是数据所在数组的首地址，指明数据存放的开始位置 */ 
    }

    return (SeqList *)ret;
}

#if 0
void SeqListDestroy(SeqList *p_list)   /* O(1) */
{
    printf("&p_list = %p.\n", &p_list);      // 0xbfbe6820 在栈里
    printf("p_list = %p.\n", p_list);       // 0x83ec008

    if(p_list)
    {
        free(p_list);
        p_list = NULL;  /* 这条语句并没什么用，可以没有，只能改变栈中p_list的值，不能改变调用此函数传的参数seq_list的值 */
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
        *pp_list = NULL; /* 可以改变调用此函数传的参数seq_list的值 */
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
        /* 修正pos值 */
        if(pos >= p_list_tmp->length)
            pos = p_list_tmp->length;   /* 为什么不是length+1?因为规定第一个元素的下标是0，即从0开始。 */

        /* 腾出空间 */
        for(i = p_list_tmp->length-1; pos <= i; i--)
            p_list_tmp->p_node[i+1] = p_list_tmp->p_node[i];
//        for(i = list_tmp_ptr->length; pos < i; i--)
//            list_tmp_ptr->node_ptr[i] = list_tmp_ptr->node_ptr[i-1];

        /* 插入 */
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

    /* 方法一: */
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
    /* 方法二: 直接调用SeqList_Get()，因为在SeqList_Get()里做了合法性的检测，所以在这里可省略合法性的检测 */
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

