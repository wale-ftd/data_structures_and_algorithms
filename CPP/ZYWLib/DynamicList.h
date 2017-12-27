#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"

namespace ZYWLib
{

template <typename T>
class DynamicList: public SeqList<T>
{
protected:
    ZYW_INT32 m_capacity; /* 顺序存储空间的大小 */

public:
    DynamicList(ZYW_INT32 capacity)   /* 申请空间 */
    {
        if(0 < capacity)
        {
            this->m_array = new T[capacity];
            if(this->m_array)
            {
                this->m_length = 0;
                m_capacity = capacity;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter capacity is invalid ...");
        }
    }

    ZYW_INT32 capacity() const
    {
        return m_capacity;
    }

    /* 重新设置顺序存储空间的大小 */
    void resize(ZYW_INT32 capacity)
    {
        if(m_capacity != capacity)
        {
            T* array = new T[capacity];
            if(array)
            {
                ZYW_INT32 len = (this->m_length<=capacity) ? this->m_length : capacity;

                for(ZYW_INT32 i = 0; i < len; i++)
                {
                    /**
                     *  1. 如果在array[i] = this->m_array[i]时触发异常(会立刻返回)，也不影响
                     *     DynamicList的正常使用，因为m_array、m_length和m_capacity的值都没有改变。
                     *     但会发生内存泄露，因为T* array = new T[capacity]出来的内存无法释放。
                     *  2. 这里触发的异常是重载的[]操作符里发生的，我们是没办法处理的，由提供重载[]操作符的人来处理。
                     */
                    array[i] = this->m_array[i];
                }

#if 1
                /* 为什么要这么写，原因见后面。 */
                T* array_tmp = this->m_array;
#else
                /**
                 *  这样写，无法保证程序是异常安全的。因为delete对象时，如果T是类对象的话，会触发它的析构函数
                 *  的调用，在这个T类的析构函数里，也许会抛出异常。如果真的抛出了异常，那就会立即返回，而此时
                 *  因为调用过析构函数m_array指向的空间可能已经被破坏了，所以原来的DynamicList也就不能再用了。
                 *  所以，不能这样写。
                 */
                if(this->m_array)
                {
                    delete [] this->m_array;
                }
#endif

                this->m_array = array;
                this->m_length = len;
                m_capacity = capacity;

                /**
                 *  如果这里发生异常(会立刻返回)也没关系，也不影响DynamicList的正常使用，因为m_array、
                 *  m_length和m_capacity的值都已经设置好了。
                 */
                if(array_tmp)
                {
                    delete [] array_tmp;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynamicList object ...");
            }
        }
    }

    ~DynamicList()  /* 归还空间 */
    {
        if(this->m_array)
        {
            delete [] this->m_array;
        }
    }
};

}


#endif // DYNAMICLIST_H
