#include <stdio.h>
#include <stdint.h>

int main()
{
    int32_t arr[4];

    char str[] = "Esto es una prueba!";
    str[3] = 0;

    printf("%s\n", str);

    return 0;
}
