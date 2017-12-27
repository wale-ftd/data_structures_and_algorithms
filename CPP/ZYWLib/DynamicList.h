#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"

namespace ZYWLib
{

template <typename T>
class DynamicList: public SeqList<T>
{
protected:
    ZYW_INT32 m_capacity; /* ˳��洢�ռ�Ĵ�С */

public:
    DynamicList(ZYW_INT32 capacity)   /* ����ռ� */
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

    /* ��������˳��洢�ռ�Ĵ�С */
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
                     *  1. �����array[i] = this->m_array[i]ʱ�����쳣(�����̷���)��Ҳ��Ӱ��
                     *     DynamicList������ʹ�ã���Ϊm_array��m_length��m_capacity��ֵ��û�иı䡣
                     *     ���ᷢ���ڴ�й¶����ΪT* array = new T[capacity]�������ڴ��޷��ͷš�
                     *  2. ���ﴥ�����쳣�����ص�[]�������﷢���ģ�������û�취����ģ����ṩ����[]����������������
                     */
                    array[i] = this->m_array[i];
                }

#if 1
                /* ΪʲôҪ��ôд��ԭ������档 */
                T* array_tmp = this->m_array;
#else
                /**
                 *  ����д���޷���֤�������쳣��ȫ�ġ���Ϊdelete����ʱ�����T�������Ļ����ᴥ��������������
                 *  �ĵ��ã������T������������Ҳ����׳��쳣���������׳����쳣���Ǿͻ��������أ�����ʱ
                 *  ��Ϊ���ù���������m_arrayָ��Ŀռ�����Ѿ����ƻ��ˣ�����ԭ����DynamicListҲ�Ͳ��������ˡ�
                 *  ���ԣ���������д��
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
                 *  ������﷢���쳣(�����̷���)Ҳû��ϵ��Ҳ��Ӱ��DynamicList������ʹ�ã���Ϊm_array��
                 *  m_length��m_capacity��ֵ���Ѿ����ú��ˡ�
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

    ~DynamicList()  /* �黹�ռ� */
    {
        if(this->m_array)
        {
            delete [] this->m_array;
        }
    }
};

}


#endif // DYNAMICLIST_H
