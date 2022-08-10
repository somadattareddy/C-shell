#ifndef __LS_H
#define __LS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>

extern int errno;

void ls_handler(char *input);
void ls_handler2(char *input);

#endif