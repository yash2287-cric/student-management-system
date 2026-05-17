#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "student.h"
#include <vector>
#include <string>

const std::string DATA_FILE = "students.dat";

// Load all student records from the binary file
std::vector<Student> loadStudents();

// Save all student records back to the binary file
void saveStudents(const std::vector<Student>& students);

#endif // FILE_HANDLER_H
