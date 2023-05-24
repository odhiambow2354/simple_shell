#include "shell.h"

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("Shell> ");
        fflush(stdout);

        fgets(command, MAX_COMMAND_LENGTH, stdin);

        // Remove newline character from the command
        command[strcspn(command, "\n")] = '\0';

        // Check if the command is "exit" to terminate the shell
        if (strcmp(command, "exit") == 0)
            break;

        // Add more logic here to handle other commands

        printf("Command not found: %s\n", command);
    }

    return 0;
}

