#include <malloc.h>
#include <stdio.h>
#include "LinkList.h"

typedef struct {
    LINK_LIST_NODE header;  /* Ϊ�˷�����ң���LINK_LIST_TYPE��LINK_LIST_NODEͳһ���������뽫header�ŵ�һ */
    int length;
} LINK_LIST_TYPE;


/* ����һ����ͷ�ڵ�ĵ������� */
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

int LinkListInsert(LINK_LIST *p_list, LINK_LIST_NODE *p_node, int pos)  /* O(n)�������ͷ��O(1)�����β��O(n) */
{
    int ret = -1;
    LINK_LIST_TYPE *p_list_tmp = (LINK_LIST_TYPE *)p_list;
    int i;
    /* ʹ��ǰ�ڵ�ָ��ָ��ͷ�ڵ� */
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list_tmp;   /* ��������������ΪLINK_LIST_TYPE��length�ź����� */

    if((NULL==p_list_tmp) || (NULL==p_node) || (0 > pos))   /* �������У��������ʱ�����ж�pos<=sList->length */
        return ret;

    /* ��������pos�� */
    #if 0
    if(p_list_tmp->length >= pos)
        pos = p_list_tmp->length;
    #endif

    /* �ҵ�Ҫ����λ�õ�ǰһ���ڵ㣬����curָ���� */
    for(i = 0; (i<pos) && cur->next; i++, cur=cur->next)
        ;

    /* ���� */
    p_node->next = cur->next;
    cur->next = p_node;

    /* ���ȼ�1 */
    p_list_tmp->length++;

    ret = 0;

    return ret;
}

LINK_LIST_NODE *LinkListGet(LINK_LIST *p_list, int pos) /* O(n)������ǻ�ȡ��һ���ڵ�O(1)����ǻ�ȡ���һ���ڵ�O(n) */
{
    LINK_LIST_NODE *ret = NULL;
    LINK_LIST_TYPE *p_list_tmp = (LINK_LIST_TYPE *)p_list;
    int i;
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list_tmp;   /* ��������������ΪLINK_LIST_TYPE��length�ź����� */

    //if((NULL==p_list_tmp) || (0 > pos))   // �޸�ǰ
    if((NULL==p_list_tmp) || (0 > pos) || (pos>=p_list_tmp->length))    // �޸ĺ�
        return ret;

    /* �ҵ�Ҫ��ȡ�ڵ��ǰһ���ڵ� */
    //for(i = 0; (i<pos) && cur->next; i++, cur=cur->next)    // �޸�ǰ
    for(i = 0; i < pos; i++, cur=cur->next)    // �޸ĺ�
        ;

    ret = cur->next;

    return ret;
}

LINK_LIST_NODE *LinkListDelete(LINK_LIST *p_list, int pos)  /* O(n)�������ɾ����һ���ڵ�O(1)�����ɾ�����һ���ڵ�O(n) */
{
    LINK_LIST_NODE *ret = NULL;
    LINK_LIST_TYPE *p_list_tmp = (LINK_LIST_TYPE *)p_list;
    int i;
    LINK_LIST_NODE *cur = (LINK_LIST_NODE *)p_list_tmp;   /* ��������������ΪLINK_LIST_TYPE��length�ź����� */

    if((NULL==p_list_tmp) || (0>pos) || (pos>=p_list_tmp->length)) {
        printf("LinkListDelete: parameter is ilegal.\n");
        return ret;
    }
    
    /* �ҵ�Ҫɾ���ڵ��ǰһ���ڵ� */
    //for(i = 0; (i<pos) && cur->next; i++, cur=cur->next)    // �޸�ǰ
    for(i = 0; i < pos; i++, cur=cur->next)    // �޸ĺ�
        ;

    ret = cur->next;

    cur->next = cur->next->next/* ret->next */;    /* ��LinkList_Get��ȣ���������������� */

    p_list_tmp->length--;

    return ret;
}

int LinkListReverse(LINK_LIST *p_list)
{
    int ret = -1;
    LINK_LIST_TYPE *p_list_tmp = (LINK_LIST_TYPE *)p_list;
    LINK_LIST_NODE *cur = ((LINK_LIST_NODE *)p_list_tmp)->next; /* ��������������ΪLINK_LIST_TYPE��length�ź����� */
    LINK_LIST_NODE *tmp_node;

    /* �޸�ǰû������Ч���ж� */
    /* �޸ĺ�û������Ч���ж� */
    if(!p_list || !cur)
        return ret;

    while(cur->next)
    {
        #if 0
        tmp_node = ((LINK_LIST_NODE *)p_list_tmp)->next;  /* �����ͷ���ָ��ĵ�һ���ڵ� */
        ((LINK_LIST_NODE *)p_list_tmp)->next = cur->next;
        cur->next = ((LINK_LIST_NODE *)p_list_tmp)->next->next;
        ((LINK_LIST_NODE *)p_list_tmp)->next->next = tmp_node;
        #else
        tmp_node = cur->next;  /* ���浱ǰָ��ָ�����һ���ڵ� */
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

