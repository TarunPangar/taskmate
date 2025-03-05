#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

static task_t todo_task;

void load_tasks()
{
    int fd = open("tasks.txt", O_RDONLY);
    if (fd == -1) return;  // No file found, start with empty list

    char buffer[MAX_NAME_LEN];
    int bytesRead;
    int offset = 0;

    while ((bytesRead = read(fd, buffer + offset, 1)) > 0) {
        if (buffer[offset] == '\n') {  // Task completed
            buffer[offset] = '\0';  // Replace newline with NULL terminator
            todo_task.name[todo_task.index] = strdup(buffer);
            todo_task.index++;
            offset = 0;
        } else {
            offset++;
        }
    }

    close(fd);
}

void add_task(const char *task_name)
{
    if (todo_task.index >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    char buffer[MAX_NAME_LEN];

    if (task_name == NULL) {  // Interactive mode
        printf("Enter task description: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline
        task_name = buffer;
    }

    todo_task.name[todo_task.index] = strdup(task_name);
    printf("Added Task: %s\n", todo_task.name[todo_task.index]);
    todo_task.index++;

    // Save to file using low-level I/O
    int fd = open("tasks.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd != -1) {
        write(fd, task_name, strlen(task_name));
        write(fd, "\n", 1);  // Add newline after task
        close(fd);
    } else {
        printf("Error: Could not save task.\n");
    }
}

void delete_task()
{
    int taskID;
    printf("\nEnter the task ID to delete: ");
    scanf("%d", &taskID);

    if (taskID < 1 || taskID > todo_task.index) {
        printf("Invalid task ID!\n");
        return;
    }

    free(todo_task.name[taskID - 1]);  // Free memory

    for (int i = taskID - 1; i < todo_task.index - 1; i++) {
        todo_task.name[i] = todo_task.name[i + 1];
    }

    todo_task.name[todo_task.index - 1] = NULL;
    todo_task.index--;

    printf("Task %d deleted.\n", taskID);

    // Rewrite file using `open()`, `write()`
    int fd = open("tasks.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd != -1) {
        for (int i = 0; i < todo_task.index; i++) {
            write(fd, todo_task.name[i], strlen(todo_task.name[i]));
            write(fd, "\n", 1);
        }
        close(fd);
    }
}

void clear_tasks()
{
    // Clear tasks in memory
    for (int i = 0; i < todo_task.index; i++) {
        free(todo_task.name[i]);
        todo_task.name[i] = NULL;
    }
    todo_task.index = 0;

    // Clear tasks in file (truncate it)
    int fd = open("tasks.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd != -1) {
        close(fd);
        printf("All tasks cleared.\n");
    } else {
        printf("Error: Could not clear tasks.\n");
    }
}

void show_tasks()
{
    if (todo_task.index == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n____TASK LIST____\n");
    for (int i = 0; i < todo_task.index; i++) {
        printf("%d. %s\n", i + 1, todo_task.name[i]);
    }
}

void exit_program()
{
	printf("\n");
	printf("Program exiting gracefully\n");
	exit(0);
}

void help()
{
    printf("\n==== TODO LIST HELP ====\n");

    printf("\n **Interactive Mode Commands:**\n");
    printf("  1. ADD Task       → Add a new task\n");
    printf("  2. DELETE Task    → Remove a task by ID\n");
    printf("  3. CLEAR Tasks    → Remove all tasks\n");
    printf("  4. SHOW Tasks     → Display all tasks\n");
    printf("  5. EXIT           → Exit the program\n");
    printf("  6. HELP           → Show this help menu\n");

    printf("\n **Command-Line Mode Options:**\n");
    printf("  - ./todo -a \"Task Description\" → Add a task\n");
    printf("  - ./todo -d TASK_ID              → Delete a task by ID\n");
    printf("  - ./todo -c                      → Clear all tasks\n");
    printf("  - ./todo -s                      → Show all tasks\n");
    printf("  - ./todo -h                      → Show this help menu\n");

    printf("\n **Examples:**\n");
    printf("  - Add a task:  `./todo -a \"Buy groceries\"`\n");
    printf("  - Delete task 2: `./todo -d 2`\n");
    printf("  - Show tasks: `./todo -s`\n");
    printf("  - Clear tasks: `./todo -c`\n");

    printf("\n Notes:\n");
    printf("  - Tasks are saved in `tasks.txt` and persist after restart.\n");
    printf("  - Use `-h` anytime for quick help.\n");

    printf("\n========================\n");
}
