#include "shell.h"
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    char *token;

    while (1) {
        printf("Shell> ");
        fgets(command, sizeof(command), stdin);

        // Remove trailing newline character
        command[strcspn(command, "\n")] = '\0';

        // Tokenize the command
        int arg_count = 0;
        token = strtok(command, " ");
        while (token != NULL && arg_count < MAX_ARGUMENTS - 1) {
            arguments[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        arguments[arg_count] = NULL; // Set the last argument to NULL for execvp()

        // Handle built-in commands
        if (strcmp(arguments[0], "exit") == 0) {
            break;
        }

        // Fork a child process
        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Fork failed\n");
            return 1;
        } else if (pid == 0) {
            // Child process
            execvp(arguments[0], arguments);
            fprintf(stderr, "Execution failed\n");
            return 1;
        } else {
            // Parent process
            wait(NULL);
        }
    }

    return 0;
}

