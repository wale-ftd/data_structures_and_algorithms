#include "Object.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace ZYWLib {

void* Object::operator new(ZYW_UINT32 size) throw()
{
    return malloc(size);
}

void Object::operator delete(void *p)
{
    if(p)
    {
        free(p);
    }
}

void* Object::operator new[](ZYW_UINT32 size) throw()
{
    return malloc(size);
}

void Object::operator delete[](void *p)
{
    if(p)
    {
        free(p);
    }
}

ZYW_BOOL Object::operator ==(const Object& obj)
{
    return (this == &obj);
}

ZYW_BOOL Object::operator !=(const Object& obj)
{
    return (this != &obj);
}

Object::~Object()
{
}

}

