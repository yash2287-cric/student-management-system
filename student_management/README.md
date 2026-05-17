# Student Management System

A console-based Student Management System written in C++ that allows you to manage student records using binary file storage.

## Features

- **Add Student** — Add a new student record with ID, name, course, GPA, and age
- **Display All Students** — View all stored student records
- **Search Student** — Search for a student by ID
- **Update Student** — Modify an existing student's details
- **Delete Student** — Remove a student record by ID

## Project Structure

```
student_management/
├── main.cpp          # Entry point, menu loop
├── student.h         # Student struct definition
├── operations.h      # Function declarations
├── operations.cpp    # Core CRUD operation implementations
├── file_handler.h    # File handler declarations
└── file_handler.cpp  # Binary file read/write logic
```

## Getting Started

### Prerequisites

- A C++ compiler (g++, MSVC, or Clang)

### Compile

Using g++:
```bash
g++ main.cpp operations.cpp file_handler.cpp -o student_management
```

### Run

```bash
./student_management
```
On Windows:
```cmd
student_management.exe
```

## Usage

When you run the program, you'll see a menu:

```
Welcome to the Student Management System
1. Add Student
2. Display All Students
3. Search Student
4. Update Student
5. Delete Student
6. Exit
```

Enter the number corresponding to the action you want to perform.

## Data Storage

Student records are stored in a binary file. Each record contains:
- **ID** — Unique integer identifier
- **Name** — Up to 50 characters
- **Course** — Up to 50 characters
- **GPA** — Float value
- **Age** — Integer

## Author

Yasvanth Dhinesh
