#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void execute_command(const char *cmd);
void display_prompt(void);
void user_input(char *cmd, size_t size);
void kel_print(const char *format);

#endif
