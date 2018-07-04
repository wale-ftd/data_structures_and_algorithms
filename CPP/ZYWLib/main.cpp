#include <iostream>
#include "GTree.h"
#include <string.h>


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

    //t.clear();
    //t.remove('D');
    SharedPointer< Tree<s8> > sp = t.remove(t.find('D'));

    const s8 *s = "KLFGMIJ";

    for(u32 i = 0; i < strlen(s); i++)
    {
        //TreeNode<s8> *node = t.find(s[i]);
        TreeNode<s8> *node = sp->find(s[i]);

        while(node)
        {
            cout << node->value << " ";

            node = node->parent;
        }

        cout << endl;
    }

    return 0;
}

