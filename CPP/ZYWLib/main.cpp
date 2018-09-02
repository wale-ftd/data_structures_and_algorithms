#include <iostream>
//#include "StaticStack.h"
#include "LinkStack.h"

using namespace std;
using namespace DSaALib;


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

s32 main(s32 argc, s8** argv)
{
#if 0
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
#else
    //StaticStack<Test, 5> stack;
    LinkStack<Test> stack;

    cout << stack.size() << endl;
#endif

    return 0;
}

