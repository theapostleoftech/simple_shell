#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stddef.h>

#define SHELL_SIGN "$ "
#define RD_SIZE 1024

void display_shell_prompt(void);
char *take_instruction(void) ;

#endif