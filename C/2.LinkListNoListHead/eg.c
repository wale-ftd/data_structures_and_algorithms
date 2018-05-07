#include "stdio.h"
#include "stdlib.h"
 
typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode;
 
typedef LNode* LinkedList;
 
LinkedList create_list()
{
    LinkedList ls = 0;
    LNode* node = 0;
    int n = 0;
 
    printf("enter the int value, other value to exit :\n");
 
    while (1)
    {
        if (scanf("%d", &n) != 1)
            break;
 
        fflush(stdin);
 
        if (node)
        {
            node->next = (LNode*)malloc(sizeof(LNode));
            node = node->next;
            node->data = n;
            node->next = 0;
        }
        else
        {
            node = (LNode*)malloc(sizeof(LNode));
            node->data = n;
            node->next = 0;
            ls = node;
        }
    }
 
    fflush(stdin);
 
    return ls;
}
 
void destroy_list(LinkedList ls)
{
    LNode* node = 0;
 
    while (ls)
    {
        node = ls;
        ls = ls->next;
        free(node);
    }
}
 
void print_list(LinkedList ls)
{
    LNode* node = ls;
 
    if (!ls)
    {
        printf("null\n");
        return;
    }
 
    while (1)
    {
        printf("%d", node->data);
         
        if (node->next)
            printf(" -> ");
        else
            break;
 
        node = node->next;
    }
 
    printf("\n");
 
}
 
void find_pos(LinkedList ls)
{
    LNode* node = ls;
    int n = 0;
    int i = 0;
 
    printf("enter the value to find : ");
    scanf("%d", &n);
    fflush(stdin);
 
    while (node)
    {
        if (node->data == n)
            printf("in pos %d\n", i);
 
        ++i;
        node = node->next;
    }
}
 
LinkedList insert_value(LinkedList ls)
{
    LNode* node = ls;
    LNode* prev = 0;
    LNode* inst = 0;
    int d = 0;
    int n = 0;
    int i = 0;
 
    printf("enter insert pos and value : ");
    scanf("%d %d", &n, &d);
    fflush(stdin);
 
    while (node)
    {
        if (i++ == n)
            break;
        prev = node;
        node = node->next;
    }
 
    if (!node)
    {
        inst = (LNode*)malloc(sizeof(LNode));
        inst->next = 0;
        inst->data = d;
 
        if (prev)
            prev->next = inst;
        else
            ls = inst;
 
        return ls;
    }
    else
    {
        if (!prev)
        {
            inst = (LNode*)malloc(sizeof(LNode));
            inst->next = ls;
            inst->data = d;
            return inst;
        }
        else
        {
            inst = (LNode*)malloc(sizeof(LNode));
            inst->next = node;
            inst->data = d;
            prev->next = inst;
            return ls;
        }
    }
}
 
LinkedList delete_value(LinkedList ls)
{
    LNode* node = ls;
    LNode* prev = 0;
    int n = 0;
 
    printf("enter the delete value : ");
    scanf("%d", &n);
    fflush(stdin);
 
    while (node)
    {
        if (node->data == n)
        {
            if (!prev)
            {
                node = node->next;
                free(ls);
                ls = node;
            }
            else
            {
                prev->next = node->next;
                free(node);
                node = prev->next;
            }
        }
        else
        {
            prev = node;
            node = node->next;
        }
    }
 
    return ls;
}
 
int main()
{
    LinkedList ls = 0;
    int op = 0;
    int quit = 0;
 
    while (quit == 0)
    {
        printf("0 : create list\n");
        printf("1 : print list\n");
        printf("2 : find value\n");
        printf("3 : insert value\n");
        printf("4 : delete value\n");
        printf("5 : exit\n");
 
        scanf("%d", &op);
        fflush(stdin);
 
        switch (op)
        {
        case 0 :
            if (ls)
                destroy_list(ls);
            ls = create_list();
            break;
 
        case 1 :
            print_list(ls);
            break;
 
        case 2 :
            find_pos(ls);
            break;
 
        case 3 :
            ls = insert_value(ls);
            break;
 
        case 4 :
            ls = delete_value(ls);
            break;
 
        case 5 :
            quit = 1;
            break;
 
        default :
            printf("error select\n");
            break;
        }
 
        printf("\n");
    }
 
    if (ls)
        destroy_list(ls);
 
    return 0;
}
