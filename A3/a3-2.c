#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct {
    char t;

    union {
        int i;
        char c;
        short s;
    } data;
} param;

void f(param p)
{
    printf("struct param {\n");
    printf("\t.t = %c\n", p.t);
    printf("\t.data = {\n");
    printf("\t\t.i = %d\n", p.data.i);
    printf("\t\t.c = %c\n", p.data.c);
    printf("\t\t.s = %d\n", p.data.s);
    printf("\t}\n");
    printf("}\n");
}

void g(void* v, char t)
{
    if (t == 'd') {
        int* i = v;
        printf("%d\n", *i);
    } else if (t == 'c') {
        char *c = v;
        printf("%c\n", *c);
    } else if (t == 'p') {
        param* p = v;
        f(*p);
    } else {
        printf("No se como interpretarlo.\n");
    }
}

int main()
{
    int a[10000000];
    int *b = malloc(sizeof(int) * 10000000);
    free(b);
    param p = {
        .t = 'c',
        .data = {
            .c = 'a'
        }
    };
    /*
    f(p);

    p.data.i = 938819649;
    f(p);
    
    p.data.c = 'a';
    f(p);*/

    /*char s[] = "Hola";

    s[1] = 0;
    printf("%s\n", s);*/

    
    /*int32_t arr[3];
    printf("arr = %p\n", arr);
    printf("&arr = %p\n", &arr);*/

    /*int i = 42;
    g(&i, 'd');

    char c = 'R';
    g(&c, 'c');

    g(&p, 'p');

    g(NULL, 'a');*/

    int32_t arr[3];
    arr[1] = 1703936;

    char *c = (char*) arr;
    printf("%d\n", *(c + 6) << 16);
}
    
