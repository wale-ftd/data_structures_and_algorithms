#ifndef __SEQ_LIST_H__
#define __SEQ_LIST_H__

typedef void SeqList;
typedef void SeqListNode;

/* 1. 创建 */
SeqList* SeqListCreate(int capacity);
/* 2. 销毁 */
#if 0
void SeqListDestroy(SeqList *p_list);
#else
void SeqListDestroy(SeqList **pp_list);
#endif
/* 3. 清空 */
void SeqListClear(SeqList *p_list);
/* 4. 获取容量 */
int SeqListCapacity(SeqList *p_list);
/* 5. 获取当前元素个数 */
int SeqListLength(SeqList *p_list);
/* 6. 插入元素 */
int SeqListInsert(SeqList *p_list, SeqListNode *p_node, int pos);
/* 7. 获取元素 */
SeqListNode* SeqListGet(SeqList *p_list, int pos);
/* 8. 删除元素 */
SeqListNode* SeqListDelete(SeqList *p_list, int pos);

/* 头插 */
static inline int SeqListInsertHead(SeqList *p_list, SeqListNode *p_node)
{
    return SeqListInsert(p_list, p_node, 0);
}
/* 尾插 */
static inline int SeqListInsertTail(SeqList *p_list, SeqListNode *p_node)
{
    return SeqListInsert(p_list, p_node, SeqListLength(p_list));
}

#endif

