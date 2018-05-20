#include <stdio.h>
#include "SeqList.h"


int main(int argc, char **argv)
{
    SeqList *seq_list = NULL;
    int index = 0;
    int a = 5;
    int b = 4;
    int c = 3;
    int d = 2;
    int e = 1;
    int f = 0;

    printf("/*-----------------create-------------------*/\n");
    seq_list = SeqListCreate(10);
    printf("capacity = %d\n", SeqListCapacity(seq_list));
    printf("length = %d\n", SeqListLength(seq_list));
    printf("\n");

    printf("/*-----------------add-------------------*/\n");
    SeqListInsertTail(seq_list, (SeqListNode *)&a);
    SeqListInsertHead(seq_list, (SeqListNode *)&b);
    SeqListInsertTail(seq_list, (SeqListNode *)&c);
    SeqListInsertHead(seq_list, (SeqListNode *)&d);
    SeqListInsertTail(seq_list, (SeqListNode *)&e);
    SeqListInsertHead(seq_list, (SeqListNode *)&f);
    for(index = 0; index < SeqListLength(seq_list); index++)
        printf("[%d] = %d\n", index, *((int *)SeqListGet(seq_list, index)));
    printf("length = %d\n", SeqListLength(seq_list));
    printf("\n");

    printf("/*-----------------detele-------------------*/\n");
    while(2 < SeqListLength(seq_list))
        //printf("del = %d\n", *((int *)(SeqListDelete(seq_list, 0))));	/* ͷɾ */
        printf("del = %d\n", *((int *)(SeqListDelete(seq_list, SeqListLength(seq_list)-1))));	/* βɾ */
        //printf("del = %d\n", *((int *)(SeqListDelete(seq_list, SeqListLength(seq_list))))); /* �������ܶ�NULLֱ�ӽ����� */
    printf("\n");

    printf("/*-----------------desplay remains-------------------*/\n");
    for(index = 0; index < SeqListLength(seq_list); index++)
        printf("[%d] = %d\n", index, *((int *)SeqListGet(seq_list, index)));
    printf("length = %d\n", SeqListLength(seq_list));
    printf("\n");

    printf("/*-----------------destroy-------------------*/\n");
    #if 0
    printf("&seq_list = %p.\n", &seq_list);                     // 0xbfbe6830
    printf("seq_list = %p.\n", seq_list);                       // 0x83ec008
    SeqListDestroy(seq_list);  /* Ϊ����seq_listָ����ڴ��ͷź�seq_list = NULL�������д��������ʵ�����ǵ��뷨 */
    printf("&seq_list = %p.\n", &seq_list);                     // 0xbfbe6830
    printf("seq_list = %p.\n", seq_list);                       // 0x83ec008, ��ΪNULL
    printf("length = %d\n", SeqListLength(seq_list));           // 2
    printf("\n");
    #else
    printf("&seq_list = %p.\n", &seq_list);                     // 0xbfbe6830
    printf("seq_list = %p.\n", seq_list);                       // 0x83ec008
    SeqListDestroy(&seq_list);  /* Ϊ����seq_listָ����ڴ��ͷź�seq_list = NULL���ɹ� */
    printf("&seq_list = %p.\n", &seq_list);                     // 0xbfbe6830
    printf("seq_list = %p.\n", seq_list);                       // NULL
    printf("length = %d\n", SeqListLength(seq_list));           // -1
    printf("\n");
    #endif

    return 0;
}



