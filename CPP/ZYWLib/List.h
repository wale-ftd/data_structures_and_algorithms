#ifndef _LIST_H_
#define _LIST_H_

#include "Object.h"

namespace DSaALib {

template <typename T>
class List: public Object 
{
protected:
    List(const List&);
    List& operator =(const List&);

public:
    List() {}
    virtual bool insert(s32 i, const T& e) = 0;
    virtual bool insert(const T& e) = 0;    /* Î²²å */
    virtual bool remove(s32 i) = 0;
    virtual bool set(s32 i, const T& e) = 0;
    virtual bool get(s32 i, T& e) const = 0;
    virtual s32 find(const T& e) const = 0;
    virtual s32 length() const = 0;
    virtual void clear() = 0;
};

}

#endif

