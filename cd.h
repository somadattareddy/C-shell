#ifndef __CD_H
#define __CD_H

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
extern int errno;

void cd_handler(char *input);

#endif