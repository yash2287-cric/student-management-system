#include "file_handler.h"
#include <fstream>
#include <iostream>

std::vector<Student> loadStudents() {
    std::vector<Student> students;
    std::ifstream file(DATA_FILE, std::ios::binary);

    if (!file.is_open()) {
        // File doesn't exist yet — first run
        return students;
    }

    Student s;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        students.push_back(s);
    }

    file.close();
    return students;
}

void saveStudents(const std::vector<Student>& students) {
    std::ofstream file(DATA_FILE, std::ios::binary | std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "[Error] Could not open data file for writing.\n";
        return;
    }

    for (const auto& s : students) {
        file.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    }

    file.close();
}
