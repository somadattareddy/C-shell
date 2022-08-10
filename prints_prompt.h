#ifndef __PRINTS_PROMPT_H
#define __PRINTS_PROMPT_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
extern int errno;

void get_names();
char *ret_home_dir();
char *ret_rel_path();
void print_prompt();
char *input_from_cmdline();

char hostname[1024];
char username[1024];
int hel;
pid_t shell_pid;

#endif