#ifndef __ECHO_H
#define __ECHO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
extern int errno;

void echo_handler(char *input);

#endif