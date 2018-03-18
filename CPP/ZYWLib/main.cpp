#include <iostream>
#include "Standard.h"

using namespace std;
//using namespace DSaALib;

u32 sum(u32 n)
{
#if 0
    if(1 < n)
    {
        return (n + sum(n-1));
    }
    else
    {
        return n;
    }
#else
    return ((1<n) ? (n+sum(n-1)) : n);
#endif
}

u32 Fibonacci(u32 n)
{
    if(2 < n)
    {
        return (Fibonacci(n-1) + Fibonacci(n-2));
    }
    else if(2 == n)
    {
        return 1;
    }
    else
    {
        return n;
    }
}

u32  mystrlen(const char *s)
{
    return (s ? ((*s)?(1+mystrlen(s+1)):0) : 0);
}

s32 main(s32 argc, s8** argv)
{
    cout << sum(100) << endl;

    cout << endl;

    for(s32 i = 1; i < 10; i++)
    {
        cout << i << ": " << Fibonacci(i) << endl;
    }

    cout << endl;

    cout << mystrlen("zyw520") << endl;

    return 0;
}

