#include <stdio.h>

typedef int(*func)(int);

int f(func g, int x)
{
    return g(x);
}

int n(int t)
{
    return t * t;
}

int main()
{
    printf("        %d\n", f(n, 2));
    return 0;
}

