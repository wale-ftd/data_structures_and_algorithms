#include <malloc.h>
#include <stdio.h>
#include "LinkList.h"

typedef struct {
    LINK_LIST_NODE header;  /* 为了方便查找，让LINK_LIST_TYPE和LINK_LIST_NODE统一起来，必须将header放第一 */
    int length;
} LINK_LIST_TYPE;


/* 创建一个带头节点的单向链表 */
LINK_LIST *LinkListCreate(void)     /* O(1) */
{
    LINK_LIST_TYPE *ret = NULL;

    ret = (LINK_LIST_TYPE *)malloc(sizeof(LINK_LIST_TYPE));
    if(ret) {
        ret->length = 0;
        ret->header.next = NULL;
    }
    
    return (LINK_LIST *)ret;
}

void LinkListDestroy(LINK_LIST **pp_list)   /* O(1) */
{
    if(*pp_list) {
        free(*pp_list);
        *pp_list = NULL;
    }
}

void LinkListClear(LINK_LIST *p_list)   /* O(1) */
{
    LINK_LIST_TYPE *p_list_tmp = (LINK_LIST_TYPE *)p_list;
    
    if(p_list_tmp) {
        p_list_tmp->length = 0;
        p_list_tmp->header.next = NULL;
    }
}

int LinkListLength(LINK_LIST *p_list)   /* O(1) */
{
    int ret = -1;
    LINK_LIST_TYPE *p_list_tmp = (LINK_LIST_TYPE *)p_list;
    
    if(p_list_tmp)
        ret = p_list_tmp->length;

    return ret;
}

int LinkListInsert(LINK_LIST *p_list, LINK_LIST_NODE *p_node, int pos)  /* O(n)。最好是头插O(1)，最坏是尾插O(n) */
{
    int ret = -1;
    LINK_LIST_TYPE *p_list_tmp = (LINK_LIST_TYPE *)p_list;
    int i;
    /* 使当前节点指针指向头节点 */
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list_tmp;   /* 可以这样做，因为LINK_LIST_TYPE中length放后面了 */

    if((NULL==p_list_tmp) || (NULL==p_node) || (0 > pos))   /* 在链表中，插入操作时不用判断pos<=sList->length */
        return ret;

    /* 不用修正pos了 */
    #if 0
    if(p_list_tmp->length >= pos)
        pos = p_list_tmp->length;
    #endif

    /* 找到要插入位置的前一个节点，并让cur指向它 */
    for(i = 0; (i<pos) && cur->next; i++, cur=cur->next)
        ;

    /* 插入 */
    p_node->next = cur->next;
    cur->next = p_node;

    /* 长度加1 */
    p_list_tmp->length++;

    ret = 0;

    return ret;
}

LINK_LIST_NODE *LinkListGet(LINK_LIST *p_list, int pos) /* O(n)。最好是获取第一个节点O(1)，最坏是获取最后一个节点O(n) */
{
    LINK_LIST_NODE *ret = NULL;
    LINK_LIST_TYPE *p_list_tmp = (LINK_LIST_TYPE *)p_list;
    int i;
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list_tmp;   /* 可以这样做，因为LINK_LIST_TYPE中length放后面了 */

    //if((NULL==p_list_tmp) || (0 > pos))   // 修改前
    if((NULL==p_list_tmp) || (0 > pos) || (pos>=p_list_tmp->length))    // 修改后
        return ret;

    /* 找到要获取节点的前一个节点 */
    //for(i = 0; (i<pos) && cur->next; i++, cur=cur->next)    // 修改前
    for(i = 0; i < pos; i++, cur=cur->next)    // 修改后
        ;

    ret = cur->next;

    return ret;
}

LINK_LIST_NODE *LinkListDelete(LINK_LIST *p_list, int pos)  /* O(n)。最好是删除第一个节点O(1)，最坏是删除最后一个节点O(n) */
{
    LINK_LIST_NODE *ret = NULL;
    LINK_LIST_TYPE *p_list_tmp = (LINK_LIST_TYPE *)p_list;
    int i;
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list_tmp;   /* 可以这样做，因为LINK_LIST_TYPE中length放后面了 */

    if((NULL==p_list_tmp) || (0>pos) || (pos>=p_list_tmp->length)) {
        printf("LinkListDelete: parameter is ilegal.\n");
        return ret;
    }
    
    /* 找到要删除节点的前一个节点 */
    //for(i = 0; (i<pos) && cur->next; i++, cur=cur->next)    // 修改前
    for(i = 0; i < pos; i++, cur=cur->next)    // 修改后
        ;

    ret = cur->next;

    cur->next = cur->next->next/* ret->next */;    /* 与LinkList_Get相比，多了以下两条语句 */

    p_list_tmp->length--;

    return ret;
}

int LinkListReverse(LINK_LIST *p_list)
{
    int ret = -1;
    LINK_LIST_TYPE *p_list_tmp = (LINK_LIST_TYPE *)p_list;
    LINK_LIST_NODE *cur = ((LINK_LIST_NODE *)p_list_tmp)->next; /* 可以这样做，因为LINK_LIST_TYPE中length放后面了 */
    LINK_LIST_NODE *tmp_node;

    /* 修改前没有做有效性判断 */
    /* 修改后没有做有效性判断 */
    if(!p_list || !cur)
        return ret;

    while(cur->next)
    {
        #if 0
        tmp_node = ((LINK_LIST_NODE *)p_list_tmp)->next;  /* 保存表头结点指向的第一个节点 */
        ((LINK_LIST_NODE *)p_list_tmp)->next = cur->next;
        cur->next = ((LINK_LIST_NODE *)p_list_tmp)->next->next;
        ((LINK_LIST_NODE *)p_list_tmp)->next->next = tmp_node;
        #else
        tmp_node = cur->next;  /* 保存当前指针指向的下一个节点 */
        cur->next = tmp_node->next;
        tmp_node->next = ((LINK_LIST_NODE *)p_list_tmp)->next;
        ((LINK_LIST_NODE *)p_list_tmp)->next = tmp_node;
        #endif
    }

    ret = 0;

    return ret;
}

#if 0
LinkList *LinkList_Reverse2(LinkList *list)
{
	TLinkList *sList = (TLinkList *)list;
	LinkListNode *curr = sList->header.next;
	LinkListNode *curr_next = curr->next;
	LinkListNode *curr_next_next = NULL;
	
	if (sList && (curr))
	{
		curr->next = NULL;
		while(curr_next)
		{
			curr_next_next = curr_next->next;
			curr_next->next = curr;
			curr = curr_next;
			curr_next = curr_next_next;	
		}
		sList->header.next = curr;
	}
	
	return sList;
}
#endif

