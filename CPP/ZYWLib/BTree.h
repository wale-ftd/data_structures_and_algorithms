#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

#undef TO_TEST
//#define TO_TEST
#ifdef TO_TEST
#include <iostream>
#endif

namespace DSaALib {

enum BT_TRAVERSAL {
    BTT_PRE_ORDER,
    BTT_IN_ORDER,
    BTT_POST_ORDER
};

template <typename T>
class BTree: public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue;

public:
    bool insert(TreeNode<T> *node)
    {
        return insert(node, BTNP_ANY);
    }

    /* virtual */ bool insert(TreeNode<T> *node, BT_NODE_POS pos)
    {
        bool ret = false;

        if(node)
        {
            if(this->m_root)
            {
                BTreeNode<T> *np = dynamic_cast<BTreeNode<T>*>(find(node->parent));

                if(np)
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
                }
            }
            else
            {
                node->parent = NULL;
                this->m_root = node;
                ret = true;
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
        return insert(value, parent, BTNP_ANY);
    }

    /* virtual */ bool insert(const T& value, TreeNode<T> *parent, BT_NODE_POS pos)
    {
        bool ret = false;
        BTreeNode<T> *nn = BTreeNode<T>::NewNode();

        if(nn)
        {
            nn->value = value;
            nn->parent = parent;

            ret = insert(nn, pos);
            if(!ret)
            {
                delete nn;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create new btree node ...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        BTree<T> *ret = NULL;

        BTreeNode<T> *node = find(value);
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
        BTree<T> *ret = NULL;

        BTreeNode<T> *obj_node = find(node);
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

    BTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T> *node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
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

    /* 将树中的所有结点清除 */
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
            BTreeNode<T> *node = m_queue.front();

            m_queue.remove();

            if(node->left)
            {
                m_queue.add(node->left);
            }

            if(node->right)
            {
                m_queue.add(node->right);
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

    SharedPointer< Array<T> > traversal(BT_TRAVERSAL order)
    {
        DynamicArray<T> *ret = NULL;
        LinkQueue<BTreeNode<T>*> lq;

        switch(order)
        {
            case BTT_PRE_ORDER:
            {
                pre_order_traversal(root(), lq);

                break;
            }
            case BTT_IN_ORDER:
            {
                in_order_traversal(root(), lq);

                break;
            }
            case BTT_POST_ORDER:
            {
                post_order_traversal(root(), lq);

                break;
            }
            default :
            {
                THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");

                break;
            }
        }

        ret = new DynamicArray<T>(lq.length());
        if(ret)
        {
            for(s32 i = 0; ret->length() > i; i++, lq.remove())
            {
                ret->set(i, lq.front()->value);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create return array ...");
        }


        return ret;
    }

    SharedPointer< BTree<T> > clone() const
    {
        BTree<T> *ret = new BTree<T>();

        if(ret)
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create new tree ...");
        }

        return ret;
    }

    bool operator ==(const BTree<T>& btree)
    {
        return equal(root(), btree.root());
    }

    bool operator !=(const BTree<T>& btree)
    {
        return !(*this == btree);
    }

    ~BTree()
    {
        clear();
    }

protected:
    /* virtual */ BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const
    {
        BTreeNode<T>* ret = NULL;

        if(node)
        {
            if(value == node->value)
            {
                ret = node;
            }
            else
            {
                if(!ret)
                {
                    ret = find(node->left, value);
                }

                if(!ret)
                {
                    ret = find(node->right, value);
                }
            }
        }

        return ret;
    }

    /* virtual */ BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T> *obj) const
    {
        BTreeNode<T>* ret = NULL;

        if(node)
        {
            if(obj == node)
            {
                ret = node;
            }
            else
            {
                if(!ret)
                {
                    ret = find(node->left, obj);
                }

                if(!ret)
                {
                    ret = find(node->right, obj);
                }
            }
        }

        return ret;
    }

    /* virtual */ bool insert(BTreeNode<T> *n, BTreeNode<T> *np, BT_NODE_POS pos)
    {
        bool ret = true;

        switch(pos)
        {
            case BTNP_ANY:
            {
                if(!np->left)
                {
                    np->left = n;
                }
                else if(!np->right)
                {
                    np->right = n;
                }
                else
                {
                    ret = false;
                }

                break;
            }
            case BTNP_LEFT:
            {
                if(!np->left)
                {
                    np->left = n;
                }
                else
                {
                    ret = false;
                }

                break;
            }
            case BTNP_RIGHT:
            {
                if(!np->right)
                {
                    np->right = n;
                }
                else
                {
                    ret = false;
                }

                break;
            }
            default:
            {
                ret = false;

                break;
            }
        }

        return ret;
    }

    /* virtual */ void remove(BTreeNode<T> *node, BTree<T> *&ret)
    {
        ret = new BTree<T>();
        if(ret)
        {
            if(node != root())
            {
                BTreeNode<T> *parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if(node == parent->left)
                {
                    parent->left = NULL;
                }
                else if(node == parent->right)
                {
                    parent->right = NULL;
                }

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

    /* virtual */ void free(BTreeNode<T> *node)
    {
        if(node)
        {
            free(node->left);

            free(node->right);

#ifdef TO_TEST
            std::cout << node->value << std::endl;
#endif
            if(node->flag())
            {
                delete node;
            }
        }
    }

    /* 计算以node为根结点的树的结点数目 */
    s32 count(BTreeNode<T> *node) const
    {
#if 0
        s32 ret = 0;

        if(node)
        {
            ret = count(node->left) + count(node->right) + 1;
        }

        return ret;
#else
        return (node ? (count(node->left)+count(node->right)+1) : 0);
#endif
    }

    /* 计算以node为根结点的树的高度 */
    s32 height(BTreeNode<T> *node) const
    {
        s32 ret = 0;

        if(node)
        {
            s32 lch = height(node->left);
            s32 rch = height(node->right);

            ret = ((lch>rch)?lch:rch) + 1;
        }

        return ret;
    }

    /* 计算以node为根结点的树的度 */
    s32 degree(BTreeNode<T> *node) const
    {
        s32 ret = 0;

        if(node)
        {
#if 1
            ret = (!!node->left) + (!!node->right);

            BTreeNode<T> *children[] = {node->left, node->right};

            for(s32 i = 0; (2>i) && (2>ret); i++)
            {
                s32 cd = degree(children[i]);

                if(cd > ret)
                {
                    ret = cd;
                }
            }
#else
            s32 lcd = degree(node->left);
            s32 rcd = degree(node->right);

            ret = (!!node->left) + (!!node->right);

            if(ret < lcd)
            {
                ret = lcd;
            }

            if(ret < rcd)
            {
                ret = rcd;
            }
#endif
        }

        return ret;
    }

    void pre_order_traversal(BTreeNode<T> *node, LinkQueue<BTreeNode<T>*>& lq)
    {
        if(node)
        {
            lq.add(node);
            pre_order_traversal(node->left, lq);
            pre_order_traversal(node->right, lq);
        }
    }

    void in_order_traversal(BTreeNode<T> *node, LinkQueue<BTreeNode<T>*>& lq)
    {
        if(node)
        {
            in_order_traversal(node->left, lq);
            lq.add(node);
            in_order_traversal(node->right, lq);
        }
    }

    void post_order_traversal(BTreeNode<T> *node, LinkQueue<BTreeNode<T>*>& lq)
    {
        if(node)
        {
            post_order_traversal(node->left, lq);
            post_order_traversal(node->right, lq);
            lq.add(node);
        }
    }

    /* copy以node为根结点的二叉树(数据元素在对应位置相等) */
    BTreeNode<T>* clone(BTreeNode<T> *node) const
    {
        BTreeNode<T> *ret = NULL;

        if(node)
        {
            ret = BTreeNode<T>::NewNode();
            if(ret)
            {
                ret->value = node->value;

                ret->left  = clone(node->left);
                if(ret->left)
                {
                    ret->left->parent = ret;
                }

                ret->right = clone(node->right);
                if(ret->right)
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node ...");
            }
        }

        return ret;
    }

    /* 判断lh为根结点的二叉树与rh为根结点的二叉树是否相等 */
    bool equal(BTreeNode<T> * lh, BTreeNode<T> * rh) const
    {
        bool ret = false;

        if(lh == rh)
        {
            ret = true;
        }
        else if(lh && rh)
        {
            ret = (lh->value==rh->value) && equal(lh->left, rh->left) && equal(lh->right, rh->right);
        }

        return ret;
    }
};

}


#endif // BTREE_H
