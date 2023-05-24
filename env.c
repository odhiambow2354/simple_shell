#include "shell.h"

extern char **environ;

int main() {
    printf("Shell> env\n");

    // Print the environment variables
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}

