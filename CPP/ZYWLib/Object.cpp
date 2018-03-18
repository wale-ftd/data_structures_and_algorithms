#include "Object.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace DSaALib {

void* Object::operator new(u32 size) throw()
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

void* Object::operator new[](u32 size) throw()
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

bool Object::operator ==(const Object& obj)
{
    return (this == &obj);
}

bool Object::operator !=(const Object& obj)
{
    return (this != &obj);
}

Object::~Object()
{
}

}

