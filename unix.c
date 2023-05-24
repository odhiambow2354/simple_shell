#include "shell.h"

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("$ ");  // Display the prompt

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;  // Handle end of file (Ctrl+D)
        }

        // Remove the trailing newline character
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "") == 0) {
            continue;  // If the user didn't enter any command, display the prompt again
        }

        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (child_pid == 0) {
            // Child process
            execlp(command, command, NULL);

            // If the command is not found, print an error message
            fprintf(stderr, "Command '%s' not found\n", command);

            exit(1);
        } else {
            // Parent process
            int status;
            waitpid(child_pid, &status, 0);
        }
    }

    return 0;
}

