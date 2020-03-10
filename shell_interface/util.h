#ifndef _UTIL_H_
#define _UTIL_H_
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#define MAX_LINE 100
#define SHELL_NAME_DIM 6
int real_dim;
typedef enum {false=0,true=1} boolean;
void clear_screen(void);
#endif
