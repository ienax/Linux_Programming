#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#define SLASH "./"

bool init_library(const char *lib_name, const char *fun_name, const char *arg) {
    int size_buf;
    char *concat_library_name;

    size_buf = (strlen(SLASH) + strlen(lib_name) + 1) * sizeof(char);
    concat_library_name = (char *) malloc(size_buf);

    strcpy(concat_library_name, SLASH);
    strcat(concat_library_name, lib_name);

    void *hdl = dlopen(concat_library_name, RTLD_LAZY);
    if (NULL == hdl)
        return false;

    int (*someSecretFunctionPrototype)(int) = (int(*)(int)) dlsym(hdl, fun_name);
    if (NULL == someSecretFunctionPrototype)
        return false;

    printf("%d\n", someSecretFunctionPrototype(atoi(arg)));
    return true;
}

int main(int argc, char * argv[])
{
    const char * name_library =     argv[1];
    const char * name_function =    argv[2];
    const char * argument =         argv[3];
    init_library(name_library, name_function, argument);
    return 0;
}
