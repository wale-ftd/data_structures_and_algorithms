#ifndef __SEQ_LIST_H__
#define __SEQ_LIST_H__

typedef void SeqList;
typedef void SeqListNode;

/* 1. ���� */
SeqList* SeqListCreate(int capacity);
/* 2. ���� */
#if 0
void SeqListDestroy(SeqList *p_list);
#else
void SeqListDestroy(SeqList **pp_list);
#endif
/* 3. ��� */
void SeqListClear(SeqList *p_list);
/* 4. ��ȡ���� */
int SeqListCapacity(SeqList *p_list);
/* 5. ��ȡ��ǰԪ�ظ��� */
int SeqListLength(SeqList *p_list);
/* 6. ����Ԫ�� */
int SeqListInsert(SeqList *p_list, SeqListNode *p_node, int pos);
/* 7. ��ȡԪ�� */
SeqListNode* SeqListGet(SeqList *p_list, int pos);
/* 8. ɾ��Ԫ�� */
SeqListNode* SeqListDelete(SeqList *p_list, int pos);

/* ͷ�� */
static inline int SeqListInsertHead(SeqList *p_list, SeqListNode *p_node)
{
    return SeqListInsert(p_list, p_node, 0);
}
/* β�� */
static inline int SeqListInsertTail(SeqList *p_list, SeqListNode *p_node)
{
    return SeqListInsert(p_list, p_node, SeqListLength(p_list));
}

#endif

