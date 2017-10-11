#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

void usage(const char **argv)
{
    fprintf(stderr, "Usage: %s <impl>", *argv);
    exit(EXIT_FAILURE);
}

int main(int argc, const char **argv)
{
    if (argc != 2) {
        usage(argv);
    }

    const char *impl_name = argv[1];
    
    void* handle = dlopen(impl_name, RTLD_NOW);
    if (handle == NULL) {
        fprintf(stderr, "dlopen: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    int(*impl)(int) = dlsym(handle, "nice_function");
    if (impl == NULL) {
        fprintf(stderr, "dlsym: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 10; i++) {
        printf("%s::nice_function(%d) -> %d\n",
               impl_name, i, impl(i));
    }
    
    return 0;
}
