#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_PATH_LENGTH 1000  // Increased buffer size for command_path

int main() {
    char path[MAX_PATH_LENGTH];
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

        // Get the PATH environment variable
        const char* env_path = getenv("PATH");

        // Copy the PATH value to path variable
        strncpy(path, env_path, MAX_PATH_LENGTH - 1);
        path[MAX_PATH_LENGTH - 1] = '\0';

        // Tokenize the path using colon (':') as the delimiter
        char* token = strtok(path, ":");

        int found_command = 0;

        // Loop through each token (directory) in the PATH
        while (token != NULL) {
            char command_path[MAX_PATH_LENGTH];

            // Construct the full path to the command
            snprintf(command_path, MAX_PATH_LENGTH, "%s/%s", token, command);

            // Check if the command exists
            if (access(command_path, X_OK) == 0) {
                found_command = 1;

                // Fork a child process
                pid_t pid = fork();

                if (pid < 0) {
                    fprintf(stderr, "Fork failed\n");
                    return 1;
                } else if (pid == 0) {
                    // Child process
                    execl(command_path, command, NULL);

                    // Exec returns only if an error occurs
                    fprintf(stderr, "Error executing command: %s\n", command);
                    exit(1);
                } else {
                    // Parent process
                    int status;
                    waitpid(pid, &status, 0);
                    break;
                }
            }

            // Move to the next token
            token = strtok(NULL, ":");
        }

        if (!found_command) {
            printf("Command not found: %s\n", command);
        }
    }

    return 0;
}

