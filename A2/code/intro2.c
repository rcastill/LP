#include <stdio.h>

union types {
    int i;
    short s;
    char c;
    float f;
};

void generic(union types t, char c)
{
    switch (c) {
    case 'i':
        printf("Entero: %d\n", t.i);
        break;
    case 's':
        printf("Short: %d\n", t.s);
        break;
    case 'c':
        printf("Char: %c\n", t.c);
        break;
    case 'f':
        printf("Float: %f\n", t.f);
        break;
    default:
        printf("Unknown\n");
    }
}

int main()
{
    union types arg = { .i = 42 };

    generic(arg, 'f');
    
    return 0;
}
