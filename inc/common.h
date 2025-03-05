#ifndef __COMMON_HEADER__
#define __COMMON_HEADER__

#include <stdio.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_NAME_LEN 100

typedef struct task {
	int index;
	char *name[MAX_NAME_LEN];
} task_t;


#endif
