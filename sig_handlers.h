#ifndef __SIG_HANDLERS_H
#define __SIG_HANDLERS_H

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

void sigchld_handler(int signo);

#endif