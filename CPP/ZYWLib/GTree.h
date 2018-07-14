#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "LinkQueue.h"

#undef TO_TEST
//#define TO_TEST
#ifdef TO_TEST
#include <iostream>
using namespace std;
#endif

namespace DSaALib {

template <typename T>
class GTree: public Tree<T>
{
protected:
    LinkQueue<GTreeNode<T>*> m_queue;

public:
    GTree()
    {
    }

    bool insert(TreeNode<T> *node)
    {
        bool ret = true;

        if(node)
        {
            if(this->m_root)
            {
                GTreeNode<T> *p_pn = find(node->parent);

                if(p_pn)
                {
                    /* 判断该父节点下，是否有与待插入节点相同的节点，防止重复插入。 */
                    GTreeNode<T> *p_cn = dynamic_cast<GTreeNode<T>*>(node);

                    /* 为什么不直接find(p_cn)，而是用p_pn->child.find(p_cn)呢？
                     * 主要是从效率方面考虑。因为find()是从树根开始查找，且上面我们已经
                     * 判断了待插入节点的父节点已经存在了，所以，仅在父节点的子节点链表中
                     * 查找即可，没有必要再从整棵树开始查找。
                     */
                    if(0 > p_pn->child.find(p_cn))
                    {
                        p_pn->child.insert(p_cn);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "Invalid parent tree node ...");
                }
            }
            else
            {
                node->parent = NULL;
                this->m_root = node;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot be NULL ...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T> *parent)
    {
        bool ret = true;
        GTreeNode<T> *p_n = GTreeNode<T>::NewNode();

        if(p_n)
        {
            p_n->parent = parent;
            p_n->value = value;

            ret = insert(p_n);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create new tree node ...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        GTree<T> *ret = NULL;

        GTreeNode<T> *node = find(value);
        if(node)
        {
            remove(node, ret);

            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value ...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T> *node)
    {
        GTree<T> *ret = NULL;

        GTreeNode<T> *obj_node = find(node);
        if(obj_node)
        {
            remove(obj_node, ret);

            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }

        return ret;
    }

    /**
     * 1. 与Tree.h相比，将返回值类型修改成了GTreeNode，合法吗？
     *    当然合法，因为赋值兼容性原则。
     * 2. const成员函数？
     *    意味着当前函数不会修改对象的状态，即在当前函数里不会修改任何成员
     *    变量的值。
     */
    GTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T>* find(TreeNode<T> *node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    s32 count() const
    {
        return count(root());
    }

    s32 degree() const
    {
        return degree(root());
    }

    s32 height() const
    {
        return height(root());
    }

    /* 将树中的所有结点清除(释放堆中的结点) */
    void clear()
    {
        free(root());

        m_queue.clear();

        this->m_root = NULL;
    }

    bool begin()
    {
        bool ret = (root() != NULL);

        if(ret)
        {
            m_queue.clear();

            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return (0 == m_queue.length());
    }

    bool next()
    {
        bool ret = (0 < m_queue.length());
        if(ret)
        {
            GTreeNode<T> *node = m_queue.front();

            m_queue.remove();

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                m_queue.add(node->child.current());
            }
        }

        return ret;
    }

    T current()
    {
        /* current()函数只有在遍历过程中才有意义 */
        if(!end())
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    ~GTree()
    {
        clear();
    }

protected:
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if(node)
        {
            if(value == node->value)
            {
                ret = node;
            }
            else
            {
                for(node->child.move(0); (!node->child.end()) && (!ret); node->child.next())
                {
                    ret = find(node->child.current(), value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;

        if(obj == node)
        {
            ret = node;
        }
        else
        {
            if(node)
            {
                for(node->child.move(0); (!node->child.end()) && (!ret); node->child.next())
                {
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }

    void free(GTreeNode<T> *node)
    {
        if(node)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                free(node->child.current());
            }

            if(node->flag())
                delete node;
#ifdef TO_TEST
            else
                cout << node->value << endl;
#endif
        }
    }

    void remove(GTreeNode<T> *node, GTree<T> *&ret)
    {
        ret = new GTree<T>();
        if(ret)
        {
            if(node != root())
            {
                LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;

                child.remove(child.find(node));

                node->parent = NULL;
            }
            else
            {
                this->m_root = NULL;
            }

            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }
    }

    /* 计算以node为根结点的树的结点数目 */
    s32 count(GTreeNode<T> *node) const
    {
        s32 ret = 0;

        if(node)
        {
            ret = 1;

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    /* 计算以node为根结点的树的高度 */
    s32 height(GTreeNode<T> *node) const
    {
        s32 ret = 0;

        if(node)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                s32 ch = height(node->child.current());

                if(ch > ret)
                {
                    ret = ch;
                }
            }

            ret += 1;
        }

        return ret;
    }

    /* 计算以node为根结点的树的度 */
    s32 degree(GTreeNode<T> *node) const
    {
        s32 ret = 0;

        if(node)
        {
            ret = node->child.length();

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                s32 cd = degree(node->child.current());

                if(cd > ret)
                {
                    ret = cd;
                }
            }
        }

        return ret;
    }
};

}



#endif // GTREE_H
