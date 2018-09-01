#include <iostream>
#include "StaticStack.h"


using namespace std;
using namespace DSaALib;


s32 main(s32 argc, s8** argv)
{
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

    return 0;
}

