#include <iostream>
#include "Standard.h"
#include <string.h>

using namespace std;
//using namespace DSaALib;

struct Node
{
    s32 value;
    Node *next;
};

Node* create_list(s32 val_base, s32 len)
{
    Node *list = NULL;
    Node *tmp_pre = NULL;
    Node *tmp = NULL;

    while(0 < len--)
    {
        tmp = new Node();
        if(tmp)
        {
            tmp->value = val_base++;
            tmp->next = NULL;

            if(list)
            {
                tmp_pre->next = tmp;
            }
            else
            {
                list = tmp;
            }

            tmp_pre = tmp;
        }
        else
        {
            /* �ڴ治�������� */
            break;
        }
    }

    return list;
}

void destroy_list(Node *list)
{
    Node *to_del = NULL;

    while(list)
    {
        to_del = list;

        list = list->next;

        delete to_del;
    }
}

void print_list(Node *list)
{
    while(list)
    {
        cout << list->value << "->";

        list = list->next;
    }

    cout << "NULL" << endl;
}

Node* reverse_list(Node *list)
{
    Node *ret = NULL;
    Node *guard = NULL;

    if((!list) || (!list->next))
    {
        ret = list;
    }
    else
    {
        guard = list->next;

        ret = reverse_list(list->next);

        guard->next = list;

        list->next = NULL;
    }

    return ret;
}

Node* merge(Node *list1, Node *list2)
{
    Node *ret = NULL;

    if(!list1)
    {
        ret = list2;
    }
    else if(!list2)
    {
        ret = list1;
    }
    else if(list1->value < list2->value)
    {
#if 0
        ret = merge(list1->next, list2);

        list1->next = ret;

        ret = list1;
#else
        ret = (list1->next = merge(list1->next, list2), list1);
#endif
    }
    else
    {
#if 0
        ret = merge(list1, list2->next);

        list2->next = ret;

        ret = list2;
#else
        ret = (list2->next = merge(list1, list2->next), list2);
#endif
    }

    return ret;
}

/**
 * HanoiTower - ��ӡ ��n��ľ�����b��a�ƶ���c �Ĳ���
 * @nr:  ľ�����
 * @src: Դ
 * @mid: ����
 * @dst: Ŀ��
 */
void HanoiTower(s32 nr, s8 src, s8 mid, s8 dst)
{
    if(0 < nr)
    {
        if(1 == nr)
        {
            cout << src << "-->" << dst << endl;
        }
        else
        {
            HanoiTower(nr-1, src, dst, mid);

            HanoiTower(1, src, mid, dst);

            HanoiTower(nr-1, mid, src, dst);
        }
    }
}

s32 swap(char *c1, char *c2)
{
    if((!c1) || (!c2))
    {
        return -1;
    }

    char tmp = *c1;
    *c1 = *c2;
    *c2 = tmp;

    return 0;
}
/**
 * permutation - ��ӡ�ַ�����ȫ����
 * @str:   ָ��Ҫ����ȫ���е����ַ���
 * @print: ���ڴ�ӡ�ַ���
 */
void permutation(char *str, char * const print)
{
    if(print)
    {
        if('\0' == *str)
        {
            cout << print << endl;
        }
        else
        {
            s32 len = strlen(str);

            for(s32 i = 0; i < len; i++)
            {
                if((0 == i) || (str[0] != str[i]))  /* �ܿ�����ͬԪ��ʱ���ظ��������е���� */
                {
                    swap(&str[0], &str[i]);

                    permutation(str+1, print);

                    swap(&str[0], &str[i]);
                }
            }
        }
    }
}

s32 main(s32 argc, s8** argv)
{
    /* ����һ���ޱ�ͷ���ĵ����� */
    Node *list = create_list(1, 5);

    print_list(list);

    list = reverse_list(list);

    print_list(list);

    /*--------------merge--------------*/
    list = reverse_list(list);

    print_list(list);

    Node *list2 = create_list(2, 6);

    print_list(list2);

    list = merge(list, list2);

    print_list(list);

    destroy_list(list);

    HanoiTower(3, 'a', 'b', 'c');

    char str[] = "abc"; /* 6�� */

    permutation(str, str);

    char str1[] = "aac";    /* 3�� */

    permutation(str1, str1);

    char str2[] = "aaa";    /* 1�� */

    permutation(str2, str2);

    return 0;
}

