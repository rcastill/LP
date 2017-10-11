#include <stdio.h>

struct B
{
    int c;
};

struct A
{
    int a;
    int b;

    struct {
        int c;
    } c;
};

void print_a(struct A a)
{
    printf("A {\n");
    printf("\t.a = %d\n", a.a);
    printf("\t.b = %d\n", a.b);
    printf("\t.c.c = %d\n", a.c.c);
    printf("}\n");
}

int main(int argc, char *argv[])
{
   struct A a = {
        .a = 1,
        .b = 2,
        .c = {
            .c = 42
        }
    };

    print_a(a);
    
    return 0;
}
