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

Object::~Object()
{
}

}

