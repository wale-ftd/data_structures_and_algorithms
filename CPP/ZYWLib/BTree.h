#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "LinkQueue.h"


namespace DSaALib {

template <typename T>
class BTree: public Tree<T>
{
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
        return NULL;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T> *node)
    {
        return NULL;

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
        return 0;
    }

    s32 degree() const
    {
        return 0;
    }

    s32 height() const
    {
        return 0;
    }

    /* 将树中的所有结点清除 */
    void clear()
    {
        this->m_root = NULL;
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
};

}


#endif // BTREE_H
