#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SHEBANG "\
#!/bin/bash \n\
"
#define SHELLSCRIPT "\
echo $argc \n\
echo $arg_1 \n\
"

unsigned int digits_in(unsigned int n);

int main(int argc, char **argv) {
    char **args_for_shell = malloc(sizeof(char *) * argc);

    unsigned int total_length = strlen(SHEBANG) + strlen(SHELLSCRIPT);

    char *argc_line;
    do {
        unsigned int arg_length = strlen("argc=") + digits_in(argc) + strlen("\n");
        argc_line = malloc(sizeof(char) * arg_length);
        snprintf(argc_line, arg_length + 1, "argc=%u\n", argc);
    } while (0);

    for (int i = 0; i < argc; i++) {
        unsigned int arg_length = strlen("arg_") + digits_in(i) + strlen("='") + strlen(argv[i]) + strlen("'\n");
        args_for_shell[i] = malloc(sizeof(char) * arg_length + 1);
        snprintf(args_for_shell[i], arg_length + 1, "arg_%u='%s'\n", i, argv[i]);
        total_length += arg_length;
    }

    char *full_script = malloc(sizeof(char) * total_length);

    *full_script = '\0';
    strcat(full_script, SHEBANG);
    strcat(full_script, argc_line);
    free(argc_line);

    for (int i = 0; i < argc; i++) {
        strcat(full_script, args_for_shell[i]);
        free(args_for_shell[i]);
    }
    free(args_for_shell);
    strcat(full_script, SHELLSCRIPT);
    int result = system(full_script);
    free(full_script);
    return result;
}

unsigned int digits_in(unsigned int n) {
    if (!n)
        return 1;
    int digits = 0;
    while (n) {
        digits++;
        n /= 10;
    }
    return digits;
}
