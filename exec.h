#ifndef __EXEC_H
#define __EXEC_H

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <signal.h>
extern int errno;

void exec_handler(char *token, char *input);

#endif