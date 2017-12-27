#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Object.h"

namespace ZYWLib
{

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception: public Object
{
protected:
    char* m_message;
    char* m_location;

private:
    void init(const char* message, const char* file, int line);

public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line);

    Exception(const Exception& e);
    Exception& operator= (const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    /**
     *  父类这里要实现这个函数吗？如果要，那又是为什么呢？
     *  答：要的。纯虚析构函数例外。C++规定：一旦自定义了析构函数，不管它是否为纯虚函数，都要实现。C++为什么
     *    会有这个规定呢？因为C++在析构一个对象的时候，最后肯定会调用父类的析构函数，你试想一下，假如父类的
     *    析构函数是一个纯虚函数，并且这个纯虚函数没有具体的实现，那这一连串的析构调用工作如何完成呢？当调用
     *    顶层父类的析构函数时，发现其没有实现，那此时你会不会觉得这更奇怪了啊！所以C++就有了这个规定。
     */
    virtual ~Exception() = 0;
};

class ArithmeticException: public Exception
{
public:
    ArithmeticException(): Exception(0) {}    /* 为什么NULL不行，0却可以。因为NULL要用到某些头文件。 */
    ArithmeticException(const char* message): Exception(message) {}
    ArithmeticException(const char* file, int line): Exception(file, line) {}
    ArithmeticException(const char* message, const char* file, int line): Exception(message, file, line) {}
    ArithmeticException(const ArithmeticException& e): Exception(e) {}

    ArithmeticException& operator= (const ArithmeticException& e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class NullPointerException: public Exception
{
public:
    NullPointerException(): Exception(0) {}    /* 为什么NULL不行，0却可以。因为NULL要用到某些头文件。 */
    NullPointerException(const char* message): Exception(message) {}
    NullPointerException(const char* file, int line): Exception(file, line) {}
    NullPointerException(const char* message, const char* file, int line): Exception(message, file, line) {}
    NullPointerException(const NullPointerException& e): Exception(e) {}

    NullPointerException& operator= (const NullPointerException& e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class IndexOutOfBoundsException: public Exception
{
public:
    IndexOutOfBoundsException(): Exception(0) {}    /* 为什么NULL不行，0却可以。因为NULL要用到某些头文件。 */
    IndexOutOfBoundsException(const char* message): Exception(message) {}
    IndexOutOfBoundsException(const char* file, int line): Exception(file, line) {}
    IndexOutOfBoundsException(const char* message, const char* file, int line): Exception(message, file, line) {}
    IndexOutOfBoundsException(const IndexOutOfBoundsException& e): Exception(e) {}

    IndexOutOfBoundsException& operator= (const IndexOutOfBoundsException& e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class NoEnoughMemoryException: public Exception
{
public:
    NoEnoughMemoryException(): Exception(0) {}    /* 为什么NULL不行，0却可以。因为NULL要用到某些头文件。 */
    NoEnoughMemoryException(const char* message): Exception(message) {}
    NoEnoughMemoryException(const char* file, int line): Exception(file, line) {}
    NoEnoughMemoryException(const char* message, const char* file, int line): Exception(message, file, line) {}
    NoEnoughMemoryException(const NoEnoughMemoryException& e): Exception(e) {}

    NoEnoughMemoryException& operator= (const NoEnoughMemoryException& e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class InvalidParameterException: public Exception
{
public:
    InvalidParameterException(): Exception(0) {}    /* 为什么NULL不行，0却可以。因为NULL要用到某些头文件。 */
    InvalidParameterException(const char* message): Exception(message) {}
    InvalidParameterException(const char* file, int line): Exception(file, line) {}
    InvalidParameterException(const char* message, const char* file, int line): Exception(message, file, line) {}
    InvalidParameterException(const InvalidParameterException& e): Exception(e) {}

    InvalidParameterException& operator= (const InvalidParameterException& e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class InvalidOperationException: public Exception
{
public:
    InvalidOperationException(): Exception(0) {}    /* 为什么NULL不行，0却可以。因为NULL要用到某些头文件。 */
    InvalidOperationException(const char* message): Exception(message) {}
    InvalidOperationException(const char* file, int line): Exception(file, line) {}
    InvalidOperationException(const char* message, const char* file, int line): Exception(message, file, line) {}
    InvalidOperationException(const InvalidOperationException& e): Exception(e) {}

    InvalidOperationException& operator= (const InvalidOperationException& e)
    {
        Exception::operator =(e);

        return *this;
    }
};

}

#endif // EXCEPTION_H
