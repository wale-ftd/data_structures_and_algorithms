#include "Exception.h"
#include <cstring>
#include <cstdlib>

using namespace std;

namespace ZYWLib
{

void Exception::init(const char* message, const char* file, int line)
{
    /**
     *  不可以。这样做是不安全的，因为无法控制message指向的外部字符串(因为message
     *  指向的字符串可能位于栈、堆或者全局数据区)的生命周期。
     */
    //m_message = message;
    m_message = message ? strdup(message) : NULL;   /* glibc-2.20里strdup的实现中未判断message为空的情况。 */

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
         *  这个分支不能要。两方面解释：
                1. 父类Exception都还没有诞生就把子类抛出，显然不符合逻辑。
                2. 分析代码走向，可以知：会陷入死循环。
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
