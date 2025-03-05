#include "task.h"
#include "common.h"

void to_options(int);

void menu()
{
/*  * TODO
    * ADD       - adds new task
    * DELETE    - deletes a task
    * SHOW	    - shows all tasks
    * CLEAR     - clears all task
*/
	int choice;

	printf("\n____MAIN_MENU____\n");
    printf("%*s",3,""); 
    printf("1. ADD task\n");
    printf("%*s",3,"");
    printf("2. DELETE task\n");
    printf("%*s",3,"");
    printf("3. CLEAR tasks\n");
    printf("%*s",3,"");
    printf("4. SHOW tasks\n");
    printf("%*s",3,"");
    printf("5. EXIT\n");
    printf("%*s",3,"");
    printf("6. HELP\n");

	printf("Please enter your choice: ");
    scanf("%d",&choice);

    while (getchar() != '\n');  // FLUSH NEWLINE FROM INPUT BUFFER

	to_options(choice);
}

void to_options(int choice)
{
	switch (choice) {
		case 1:
			add_task(NULL);
			break;
		case 2:
			delete_task();
			break;
		case 3:
			clear_tasks();
			break;
		case 4:
			show_tasks();
			break;
		case 5:
			exit_program();
			break;
		default:
			help();
			break;
	}
}

void parse_argc(int argc, char **argv)
{
	int choice, opt;
	char *task_description = NULL;

	while ((opt = getopt(argc, argv, "a:d:csh")) != -1) {
		switch (opt) {
			case 'a':
				task_description = optarg; // Capture the argument for add_task
				choice = 1;
				break;
			case 'd':
				choice = 2;
				break;
			case 'c':
				choice = 3;
				break;
			case 's':
				choice = 4;
				break;
            default:
                choice = 6;
                break;
		}
	}

	if (choice == 1 && task_description != NULL) {
		add_task(task_description);
	} else {
		to_options(choice);
	}
}
