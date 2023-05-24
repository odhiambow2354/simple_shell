//shell.h
#ifndef SHELL_H
#define SHELL_H

/*--Libraries*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

/*---Prototypes---*/

/**
 * Reads a line of input from the user.
 * Returns an allocated string containing the line, or NULL if no more input is available.
 */
char* custom_getline();

/**
 * Frees the memory allocated for a line.
 * This function releases the memory returned by custom_getline().
 */
void free_line(char* line);


/**
 * Tokenizes a line into an array of arguments.
 * Returns the number of arguments found.
 */
int tokenize_line(char* line, char** arguments, int max_arguments);

/**
 * Executes the command entered by the user.
 * Returns 1 if the command was executed successfully, 0 otherwise.
 */
int execute_command(char** arguments, int num_arguments);

/**
 * Implements the built-in "exit" command to terminate the shell.
 * Usage: exit
 */
void exit_shell();

/**
 * Implements the built-in "env" command to print the current environment.
 * Usage: env
 */
void print_environment();

#endif
