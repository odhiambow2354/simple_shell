#include "shell.h"

#define MAX_INPUT_LENGTH 100

char* custom_getline() {
    static char buffer[MAX_INPUT_LENGTH];
    static size_t buffer_index = 0;
    static ssize_t chars_read = 0;

    // Check if we need to read more characters into the buffer
    if (buffer_index >= chars_read) {
        chars_read = read(STDIN_FILENO, buffer, MAX_INPUT_LENGTH);
        buffer_index = 0;

        // If there are no more characters to read, return NULL
        if (chars_read <= 0)
            return NULL;
    }

    // Find the end of the line or buffer
    size_t line_end = buffer_index;
    while (line_end < chars_read && buffer[line_end] != '\n')
        line_end++;

    // Allocate memory for the line
    char* line = (char*)malloc(line_end - buffer_index + 1);
    if (line == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Copy the line from the buffer to the allocated memory
    size_t i, j = 0;
    for (i = buffer_index; i < line_end; i++, j++)
        line[j] = buffer[i];
    line[j] = '\0';

    // Update the buffer index for the next call to custom_getline
    buffer_index = line_end + 1;

    return line;
}

int main() {
    while (1) {
        printf("Shell> ");
        fflush(stdout);

        char* line = custom_getline();

        // Check if custom_getline returns NULL (no more input)
        if (line == NULL)
            break;

        // Process the line or execute commands here

        printf("You entered: %s\n", line);
        free(line);
    }

    return 0;
}

