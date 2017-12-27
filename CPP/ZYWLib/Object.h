#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Standard.h"

namespace ZYWLib {

class Object {
public:
    void* operator new(ZYW_UINT32 size) throw();
    void operator delete(void *p);
    void* operator new[](ZYW_UINT32 size) throw();
    void operator delete[](void *p);

    virtual ~Object() = 0;
};



}

#endif

