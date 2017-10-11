#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct gll_node
{
    struct gll_node *next;
    struct gll_node *prev;

    size_t size;
    char data[];

} *__gll_node_t;

typedef struct
{
    struct gll_node *head;
    struct gll_node *tail;

    size_t count;

} *gll_t;

void __gll_node_init(__gll_node_t node, const void* data, size_t size)
{
    // Set everything to 0
    node->next = 0;
    node->prev = 0;
    node->size = size;
    memcpy(node->data, data, size);
}

__gll_node_t __gll_node_create(const void *data, size_t size)
{
    // Allocate
    __gll_node_t node = malloc(sizeof(*node) + size);
    // Initialize node
    __gll_node_init(node, data, size);

    return node;
}

void __gll_init(gll_t gll)
{
    memset(gll, 0, sizeof(*gll));
}

gll_t gll_create()
{
    // Allocate
    gll_t gll  = malloc(sizeof(*gll));
    // Initialize
    __gll_init(gll);

    return gll;
}

void gll_add(gll_t gll, const void *data, size_t size)
{
    __gll_node_t node = __gll_node_create(data, size);

    if (gll->tail != NULL) {
        gll->tail->next = node;
        node->prev = gll->tail;
    } else {
        gll->head = node;
        node->prev = node;
    }

    node->next = gll->head;
    gll->tail = node;

    gll->count++;
}

void gll_debug(const gll_t gll, void(*cb)(const void*, size_t))
{
    printf("[");
    __gll_node_t it = gll->head;
    for (int i = 0; i < gll->count - 1; i++) {
        cb(it->data, it->size);
        it = it->next;
        printf(", ");
    }
    cb(it->data, it->size);
    printf("]\n");
}

typedef struct
{
    char t;

    union {
        char   c;
        short  s;
        int    i;
        long   l;
        float  f;
        double d;
        char*  S;

    } d;
    
} poly_t;

void print_string(const void *str_v, size_t ssize)
{
    const char *str = str_v;
    printf("\"%s\"", str);
}

void print_poly(const void *poly_v, size_t ssize)
{
    const poly_t *poly = poly_v;

    switch (poly->t) {
    case 'c':
        printf("%c", poly->d.c);
        break;
    case 's':
        printf("%d", poly->d.s);
        break;
    case 'i':
        printf("%i", poly->d.i);
        break;
    case 'l':
        printf("%ld", poly->d.l);
        break;
    case 'f':
        printf("%f", poly->d.f);
        break;
    case 'd':
        printf("%lf", poly->d.d);
        break;
    case 'S':
        printf("\"%s\"", poly->d.S);
        break;
    default:
        printf("Unreachable!");
    }
}

int main()
{
    gll_t gll_strings = gll_create();

    gll_add(gll_strings, "This is not fair", 17);
    gll_add(gll_strings, "But it works", 14);

    gll_debug(gll_strings, print_string);

    gll_t gll = gll_create();

    poly_t item1 = {
        .t = 'i',
        .d = {
            .i = 42
        }
    };

    poly_t item2 = {
        .t = 'S',
        .d = {
            .S = "The answer"
        }
    };

    int integer = 213;
    
    gll_add(gll, &item1, sizeof(item1));
    gll_add(gll, &item2, sizeof(item2));
    gll_add(gll, &integer, sizeof(integer));


    int dst;
    memcpy(&dst, gll->head->next->next->data, sizeof(dst));
    printf("%d\n", dst);
    
    gll_debug(gll, print_poly);

    free(gll);
    free(gll_strings);

    return 0;
}
