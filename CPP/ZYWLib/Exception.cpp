#include "Exception.h"
#include <cstring>
#include <cstdlib>

using namespace std;

namespace ZYWLib
{

void Exception::init(const char* message, const char* file, int line)
{
    /**
     *  �����ԡ��������ǲ���ȫ�ģ���Ϊ�޷�����messageָ����ⲿ�ַ���(��Ϊmessage
     *  ָ����ַ�������λ��ջ���ѻ���ȫ��������)���������ڡ�
     */
    //m_message = message;
    m_message = message ? strdup(message) : NULL;   /* glibc-2.20��strdup��ʵ����δ�ж�messageΪ�յ������ */

    if(file)
    {
        char sl[16] = {0};

        itoa(line, sl, 10);

        m_location = static_cast<char *>(malloc(strlen(file) + strlen(sl) + 2));
        if(m_location)
        {
            m_location = strcpy(m_location, file);
            m_location = strcat(m_location, ":");
            m_location = strcat(m_location, sl);
        }
#if 0
        /**
         *  �����֧����Ҫ����������ͣ�
                1. ����Exception����û�е����Ͱ������׳�����Ȼ�������߼���
                2. �����������򣬿���֪����������ѭ����
         */
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "Exception::init");
        }
#endif
    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception(const char* message)
{
    init(message, NULL, 0);
}

Exception::Exception(const char* file, int line)
{
    init(NULL, file, line);
}

Exception::Exception(const char* message, const char* file, int line)
{
    init(message, file, line);
}

Exception::Exception(const Exception& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

Exception& Exception::operator= (const Exception& e)
{
    if(this != &e)
    {
        if(m_message)
        {
            free(m_message);
        }

        if(m_location)
        {
            free(m_location);
        }

        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }

    return *this;
}

const char* Exception::message() const
{
    return m_message;
}

const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    if(m_message)
    {
        free(m_message);
    }

    if(m_location)
    {
        free(m_location);
    }
}

}
