#include <iostream>
#include "StaticStack.h"
#include "LinkStack.h"

using namespace std;
using namespace DSaALib;

//#define _STATIC_STACK_TEST_
//#define _STATIC_STACK_TEST_CLASS_OBJ_
//#define _LINK_STACK_TEST_
#define _LINK_STACK_TEST_SIGN_MATCH

#if defined(_STATIC_STACK_TEST_CLASS_OBJ_) || defined(_LINK_STACK_TEST_)
class Test: public Object
{
public:
    Test()
    {
        cout << "Test()" << endl;
    }

    ~Test()
    {
        cout << "~Test()" << endl;
    }
};
#endif

#ifdef _LINK_STACK_TEST_SIGN_MATCH
bool is_left(s8 c)
{
    return ('('==c) || ('['==c) || ('{'==c) || ('<'==c);
}

bool is_right(s8 c)
{
    return (')'==c) || (']'==c) || ('}'==c) || ('>'==c);
}

bool is_quot(s8 c)
{
    return ('\"'==c) || ('\''==c);
}

bool is_match(s8 l, s8 r)
{
    return (('('==l)&&(')'==r)) ||
           (('['==l)&&(']'==r)) ||
           (('{'==l)&&('}'==r)) ||
           (('<'==l)&&('>'==r)) ||
           (('\"'==l)&&('\"'==r)) ||
           (('\''==l)&&('\''==r));
}

bool scan(const s8 *s)
{
    bool ret = true;
    LinkStack<s8> stack;

    s = s ? s : "";

    for(s32 i = 0; ret && s[i]; i++)
    {
        s8 cur = s[i];

        if(is_left(cur))
        {
            stack.push(cur);
        }
        else if(is_right(cur))
        {
            if(0<stack.size() && is_match(stack.top(), cur))
            {
                stack.pop();
            }
            else
            {
                ret = false;
            }
        }
        else if(is_quot(cur))
        {
            if(0 == stack.size())
            {
                stack.push(cur);
            }
            else
            {
                if(is_match(stack.top(), cur))
                {
                    stack.pop();
                }
                else
                {
                    stack.push(cur);
                }
            }
        }
    }

    return ret && (0==stack.size());
}
#endif

s32 main(s32 argc, s8** argv)
{
#ifdef _STATIC_STACK_TEST_
    StaticStack<s32, 5> stack;

    try {
        stack.pop();
    }
    catch(const Exception& e) {
        cout << e.message() << endl;
        cout << e.location() << endl;
    }

    for(s32 i = 0; i < 5; i++)
    //for(s32 i = 0; i < 6; i++)
    {
        stack.push(i);
    }

    while(stack.size() > 0)
    {
        cout << stack.top() << endl;

        stack.pop();
    }

#elif defined(_STATIC_STACK_TEST_CLASS_OBJ_)
    StaticStack<Test, 5> stack;
    cout << stack.size() << endl;
#elif defined(_LINK_STACK_TEST_)
    LinkStack<Test> stack;
    cout << stack.size() << endl;
#elif defined(_LINK_STACK_TEST_SIGN_MATCH)
    //s8 s[] = "abcd";
    //s8 s[] = "\"<a{b[(\'x\')]c}d>\"";
    //s8 s[] = "(";
    //s8 s[] = "]";
    s8 s[] = "else if(is_quot(cur)){if(0 == stack.size()){stack.push(cur);}else{if(is_match(stack.top(), cur)){stack.pop();}else{stack.push(cur);}}}";
    cout << scan(s) << endl;
#endif

    return 0;
}

