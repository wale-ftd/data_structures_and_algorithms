#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Standard.h"

namespace DSaALib {

class Object {
public:
    void* operator new(u32 size) throw();
    void operator delete(void *p);
    void* operator new[](u32 size) throw();
    void operator delete[](void *p);
    bool operator ==(const Object& obj);
    bool operator !=(const Object& obj);

    virtual ~Object() = 0;
};

}

#endif

