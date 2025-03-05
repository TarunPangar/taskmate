# TaskMate

TaskMate is a simple and efficient **command-line to-do list manager** written in C. It supports both **interactive mode** and **command-line mode**, allowing users to **add, delete, clear, and display tasks** easily. Tasks are stored in a file (`tasks.txt`), ensuring persistence across sessions.

## Features
- Interactive menu for easy task management  
- Command-line options (`-a`, `-d`, `-s`, `-c`, `-h`) for quick actions  
- Saves tasks persistently using file operations (`open()`, `read()`, `write()`)  
- Lightweight and fast  

## Installation
```sh
# Clone the repository
git clone https://github.com/TarunPangar/taskmate.git
cd taskmate

# Compile the program
make
```

## Usage
### Interactive Mode
Run TaskMate without arguments to enter the interactive menu:
```sh
./todo
```
You will see:
```
____MAIN_MENU____
   1. ADD task
   2. DELETE task
   3. CLEAR tasks
   4. SHOW tasks
   5. EXIT
   6. HELP
Please enter your choice:
```

### Command-Line Mode
TaskMate also supports quick commands:
```sh
./todo -a "Buy groceries"  # Add a task
./todo -d 2               # Delete task 2
./todo -c                 # Clear all tasks
./todo -s                 # Show tasks
./todo -h                 # Show help menu
```

## Examples
```sh
$ ./todo -a "Read a book"
Task added: Read a book

$ ./todo -s
1. Read a book

$ ./todo -d 1
Task deleted: Read a book

$ ./todo -c
All tasks cleared.
```

## Contributing
1. Fork the repository
2. Create a new branch (`git checkout -b feature-branch`)
3. Commit your changes (`git commit -m "Add new feature"`)
4. Push to the branch (`git push origin feature-branch`)
5. Open a Pull Request
