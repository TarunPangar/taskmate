#include <stdio.h>

#include "options.h"
#include "task.h"

int main(int argc, char *argv[])
{
    load_tasks();
	if(argc == 1) {
		while (1) {
			menu();
        }
	} else {
		parse_argc(argc, argv);
	}

	return 0;
}
