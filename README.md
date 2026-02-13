# TO-DO List Manager

A console-based task management application built in C++ that helps users organize their daily tasks efficiently.

## Project Overview

This is **Task 1** from my CodeAlpha internship program. The application allows users to manage tasks with features like adding, viewing, updating, and deleting tasks, along with persistent storage using CSV files.

## Features

- **Add Tasks** - Create new tasks with categories and descriptions
- **Mark Tasks** - Set tasks as pending or completed
- **View Tasks** - Filter by status (pending/completed) and category
- **Update Tasks** - Modify task descriptions and status
- **Delete Tasks** - Remove individual tasks or entire list
- **Persistent Storage** - Tasks are saved to CSV file automatically
- **Categorization** - Organize tasks by Personal, Work, or Education

## Technologies Used

- **Language:** C++
- **Concepts:** 
  - Object-Oriented Programming (Classes)
  - File I/O Operations
  - Vector (STL)
  - String Stream
  - Control Structures (Loops, Conditionals, Switch-Case)

## Requirements

- C++ Compiler (GCC, MinGW, or MSVC)
- C++11 or later

## How to Run

### Compilation

```bash
# Using g++
g++ main.cpp -o todo

# Using MinGW (Windows)
g++ main.cpp -o todo.exe
```

### Execution

```bash
# Linux/Mac
./todo

# Windows
todo.exe
```

## Usage Guide

### Main Menu Options:

1. **Add Task** - Create a new task
   - Select category (Personal/Work/Education)
   - Enter description
   - Set initial status

2. **View Task** - Display tasks
   - Choose pending or completed
   - Filter by category or view all

3. **Update Task** - Modify existing task
   - Update description
   - Change status

4. **Delete Task** - Remove task by ID

5. **Delete List** - Clear entire task list

6. **Exit** - Close the application

### Example Workflow:

```
1. Select "1" to add a task
2. Choose category: "1" for Personal
3. Enter description: "Buy groceries"
4. Set status: "1" for Pending
5. Task is saved automatically!
```

## File Structure

```
todo-list-manager/
├── main.cpp          # Main source code
├── TaskFile.csv      # Auto-generated task storage
├── README.md         # Documentation
└── .gitignore        # Git ignore rules
```

## Learning Outcomes

Through this project, I learned:
- Implementing OOP principles in C++
- File handling and data persistence
- Input validation and error handling
- Working with STL containers (vectors)
- CSV file parsing and manipulation
- Building user-friendly console interfaces

## Known Issues / Future Improvements

- [ ] Add task priority levels
- [ ] Implement due dates for tasks
- [ ] Add search functionality
- [ ] Support for multiple users
- [ ] Export tasks to different formats

## Author

**Your Name**
- Intern at CodeAlpha
- Task: TO-DO List Application

## License

This project is part of the CodeAlpha internship program.

## Acknowledgments

- CodeAlpha for the internship opportunity
- C++ community for documentation and resources

---
