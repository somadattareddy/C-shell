#ifndef __PINFO_H
#define __PINFO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
extern int errno;

void pinfo_handler(char *input);

#endif