#ifndef STATICLIST_H
#define STATICLIST_H

#include "SeqList.h"

namespace DSaALib
{

template <typename T, s32 N>
class StaticList: public SeqList<T>
{
protected:
    T m_space[N];   /* 顺序存储空间，N为模板参数 */

public:
    StaticList()   /* 指定父类成员的具体值 */
    {
        this->m_array = m_space;    /* 为什么m_array = m_space会编译报错呢？ */
        this->m_length = 0;         /* 为什么m_length = 0会编译报错呢？ */
    }
    s32 capacity() const
    {
        return N;
    }
};


}

#endif // STATICLIST_H
