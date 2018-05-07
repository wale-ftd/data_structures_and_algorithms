
#ifndef __LINK_LIST__
#define __LINK_LIST__

typedef void LINK_LIST;
struct _tag_link_list_ {
    struct _tag_link_list_ *next;
};
typedef struct _tag_link_list_ LINK_LIST_NODE;

LINK_LIST *LinkListCreate(void);

void LinkListDestroy(LINK_LIST **pp_list);

void LinkListClear(LINK_LIST **pp_list);

int LinkListLength(LINK_LIST *p_list);

int LinkListInsert(LINK_LIST **pp_list, LINK_LIST *p_list, LINK_LIST_NODE *p_node, int pos);

LINK_LIST_NODE *LinkListGet(LINK_LIST *p_list, int pos);

LINK_LIST_NODE *LinkListDelete(LINK_LIST **pp_list, LINK_LIST *p_list, int pos);

/* Í·²å */
static inline int LinkListInsertHead(LINK_LIST **pp_list, LINK_LIST *p_list, LINK_LIST_NODE *p_node)
{
    return LinkListInsert(pp_list, p_list, p_node, 0);
}
#if 0
/* Î²²å */
static inline int LinkListInsertTail(LINK_LIST *p_list, LINK_LIST_NODE *p_node)
{
    return LinkListInsert(p_list, p_node, LinkListLength(p_list));
}
#endif

#endif


