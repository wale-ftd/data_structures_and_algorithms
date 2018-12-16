#ifndef STATICLIST_H
#define STATICLIST_H

#include "SeqList.h"

namespace DSaALib
{

template <typename T, s32 N>
class StaticList: public SeqList<T>
{
protected:
    T m_space[N];   /* ˳��洢�ռ䣬NΪģ����� */

public:
    StaticList()   /* ָ�������Ա�ľ���ֵ */
    {
        this->m_array = m_space;    /* Ϊʲôm_array = m_space����뱨���أ� */
        this->m_length = 0;         /* Ϊʲôm_length = 0����뱨���أ� */
    }
    s32 capacity() const
    {
        return N;
    }
};


}

#endif // STATICLIST_H
