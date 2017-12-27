#ifndef _LIST_H_
#define _LIST_H_

#include "Object.h"

namespace ZYWLib {

template <typename T>
class List: public Object 
{
protected:
    List(const List&);
    List& operator =(const List&);

public:
    List() {}
    virtual ZYW_BOOL insert(ZYW_INT32 i, const T& e) = 0;
    virtual ZYW_BOOL insert(const T& e) = 0;    /* Î²²å */
    virtual ZYW_BOOL remove(ZYW_INT32 i) = 0;
    virtual ZYW_BOOL set(ZYW_INT32 i, const T& e) = 0;
    virtual ZYW_BOOL get(ZYW_INT32 i, T& e) const = 0;
    virtual ZYW_INT32 length() const = 0;
    virtual void clear() = 0;
};


}

#endif

