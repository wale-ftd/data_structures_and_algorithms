#include <iostream>
#include "GTree.h"
#include <string.h>
#include "BTree.h"


using namespace std;
using namespace DSaALib;

s32 main(s32 argc, s8** argv)
{
    GTree<s8> t;
    GTreeNode<s8> *node = NULL;
    GTreeNode<s8> root;

    root.value = 'A';
    root.parent = NULL;

    /**
     * root�ĳ���ջ�ϣ���clear������delete root��㣬������
     * ����Ҳû���⣬Ϊʲô�أ���Ϊ���main����̫�򵥵ģ�����û
     * ���ü���¶������
     */
    t.insert(&root);

    node = t.find('A');
    t.insert('B', node);
    t.insert('C', node);
    t.insert('D', node);

    node = t.find('B');
    t.insert('E', node);
    t.insert('F', node);

    node = t.find('E');
    t.insert('K', node);
    t.insert('L', node);

    node = t.find('C');
    t.insert('G', node);

    node = t.find('D');
    t.insert('H', node);
    t.insert('I', node);
    t.insert('J', node);

    node = t.find('H');
    t.insert('M', node);

    cout << t.count() << endl;

    cout << t.height() << endl;

    cout << t.degree() << endl;

    for(t.begin(); !t.end(); t.next())
    {
        cout << t.current() << endl;
    }

    BTree<s32> bt;
    BTreeNode<s32> btn;

    return 0;
}

