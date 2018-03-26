#include <iostream>
#include "Standard.h"
#include <string.h>
#include "LinkList.h"

using namespace std;
using namespace DSaALib;

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

/**
 * r_print_even - �����ӡż�ڵ�
 * @list: ����
 */
void r_print_even(const Node * const list)
{
    if(list)
    {
        r_print_even(list->next);

        if(0 == (list->value%2))
        {
            cout << list->value << endl;
        }
    }
}

template <s32 SIZE>
class QueueSolution: public Object
{
protected:
    enum {N = SIZE + 2}; /* ΪʲôҪ��2����ʶ���ұ߽磬�����̡� */

    struct Pos: public Object
    {
        Pos(s32 px = 0, s32 py = 0): x(px), y(py) {}
        s32 x;
        s32 y;
    };

    s32 m_chessboard[N][N];
    Pos m_direction[3];
    LinkList<Pos> m_solution;
    s32 m_count;

private:
    void init()
    {
        for(s32 i = 0; i < N; i++)
        {
            for(s32 j = 0; j < N; j++)
            {
                if((0==i) || (0==j) || ((N-1)==i) || ((N-1)==j))
                {
                    m_chessboard[i][j] = 2;
                }
                else
                {
                    m_chessboard[i][j] = 0;
                }
            }
        }

        m_direction[0].x = -1;
        m_direction[0].y = -1;
        m_direction[1].x = 0;
        m_direction[1].y = -1;
        m_direction[2].x = 1;
        m_direction[2].y = -1;

        m_count = 0;
    }

    void print_chessboard()
    {
        if(m_count)
        {
            cout << m_count << ": ";

            for(m_solution.move(0); !m_solution.end(); m_solution.next())
            {
                cout << "(" << m_solution.current().x << "," << m_solution.current().y << ")  ";
            }

            cout << endl;
        }

        for(s32 i = N-1; i >=0; i--)
        //for(s32 i = 0; i < N; i++)
        {
            for(s32 j = 0; j < N; j++)
            {
                switch(m_chessboard[i][j])
                {
                    case 0:
                    {
                        cout << " ";
                        break;
                    }
                    case 1:
                    {
                        cout << "#";
                        break;
                    }
                    case 2:
                    {
                        cout << "*";
                        break;
                    }
                }
            }

            cout << endl;
        }

        cout << endl;
    }

    bool check(s32 x, s32 y, s32 d)
    {
        bool flag = true;

        do
        {
            x += m_direction[d].x;
            y += m_direction[d].y;
            flag = flag && (0==m_chessboard[x][y]);
        } while(flag);

        return (2 == m_chessboard[x][y]); /* �ܹ�����߽��˵���÷�������û�����ʺ�� */
    }

    void run(s32 j)
    {
        if(SIZE >= j)
        {
            for(s32 i = 1; i <= SIZE; i++)
            {
                if(check(i, j, 0) && check(i, j, 1) && check(i, j, 2))
                {
                    m_chessboard[i][j] = 1;

                    m_solution.insert(Pos(i, j));

                    run(j + 1);

                    m_chessboard[i][j] = 0;

                    m_solution.remove(m_solution.length() - 1);
                }
            }
        }
        else
        {
            m_count++;

            print_chessboard();
        }
    }

public:
    QueueSolution()
    {
        init();
        print_chessboard();
    }

    void run()
    {
        run(1);
    }
};

s32 main(s32 argc, s8** argv)
{
    /* ����һ���ޱ�ͷ���ĵ����� */
    Node *list = create_list(1, 5);
    print_list(list);
    list = reverse_list(list);
    print_list(list);
    destroy_list(list);

    /*--------------merge--------------*/
    cout << endl;
    cout << "----------merge-----------" << endl;
    list = create_list(1, 5);
    Node *list2 = create_list(2, 6);
    print_list(list);
    print_list(list2);
    list = merge(list, list2);
    print_list(list);
    destroy_list(list);

    /*----------��ŵ��-----------*/
    cout << endl;
    cout << "----------��ŵ��-----------" << endl;
    HanoiTower(3, 'a', 'b', 'c');

    /*----------ȫ����-----------*/
    cout << endl;
    cout << "----------ȫ����-----------" << endl;
    char str[] = "abc"; /* 6�� */
    permutation(str, str);
    char str1[] = "aac";    /* 3�� */
    permutation(str1, str1);
    char str2[] = "aaa";    /* 1�� */
    permutation(str2, str2);

    /*----------�����ӡż�ڵ�-----------*/
    cout << endl;
    cout << "----------�����ӡż�ڵ�-----------" << endl;
    list = create_list(1, 10);
    print_list(list);
    r_print_even(list);
    destroy_list(list);

    /*----------�˻ʺ�����-----------*/
    cout << endl;
    cout << "----------�˻ʺ�����-----------" << endl;
    QueueSolution<8> qs;
    qs.run();

    return 0;
}

