#include "operations.h"
#include "file_handler.h"
#include "student.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <limits>

// ─── Helpers ────────────────────────────────────────────────────────────────

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void printDivider() {
    std::cout << std::string(70, '-') << "\n";
}

static void printHeader() {
    printDivider();
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(20) << "Name"
              << std::setw(20) << "Course"
              << std::setw(8)  << "Age"
              << std::setw(6)  << "GPA"
              << "\n";
    printDivider();
}

static void printStudent(const Student& s) {
    std::cout << std::left
              << std::setw(6)  << s.id
              << std::setw(20) << s.name
              << std::setw(20) << s.course
              << std::setw(8)  << s.age
              << std::fixed << std::setprecision(2) << std::setw(6) << s.gpa
              << "\n";
}

// Returns true if an ID already exists in the list
static bool idExists(const std::vector<Student>& students, int id) {
    return std::any_of(students.begin(), students.end(),
                       [id](const Student& s) { return s.id == id; });
}

// ─── Operations ─────────────────────────────────────────────────────────────

void addStudent() {
    std::vector<Student> students = loadStudents();
    Student s;

    std::cout << "\n=== Add New Student ===\n";

    // ID — must be positive and unique
    while (true) {
        std::cout << "Enter Student ID (positive integer): ";
        if (std::cin >> s.id && s.id > 0) {
            if (idExists(students, s.id)) {
                std::cout << "[Error] ID " << s.id << " already exists. Try another.\n";
            } else {
                break;
            }
        } else {
            std::cout << "[Error] Invalid ID. Please enter a positive integer.\n";
            clearInput();
        }
    }
    clearInput();

    // Name
    std::cout << "Enter Name: ";
    std::cin.getline(s.name, 50);

    // Course
    std::cout << "Enter Course: ";
    std::cin.getline(s.course, 50);

    // Age
    while (true) {
        std::cout << "Enter Age: ";
        if (std::cin >> s.age && s.age > 0 && s.age < 150) break;
        std::cout << "[Error] Invalid age.\n";
        clearInput();
    }

    // GPA
    while (true) {
        std::cout << "Enter GPA (0.0 - 4.0): ";
        if (std::cin >> s.gpa && s.gpa >= 0.0f && s.gpa <= 4.0f) break;
        std::cout << "[Error] GPA must be between 0.0 and 4.0.\n";
        clearInput();
    }
    clearInput();

    students.push_back(s);
    saveStudents(students);
    std::cout << "[Success] Student record added.\n";
}

void displayAllStudents() {
    std::vector<Student> students = loadStudents();

    std::cout << "\n=== All Student Records ===\n";

    if (students.empty()) {
        std::cout << "No records found.\n";
        return;
    }

    printHeader();
    for (const auto& s : students) {
        printStudent(s);
    }
    printDivider();
    std::cout << "Total records: " << students.size() << "\n";
}

void searchStudent() {
    std::vector<Student> students = loadStudents();

    if (students.empty()) {
        std::cout << "\nNo records to search.\n";
        return;
    }

    std::cout << "\n=== Search Student ===\n";
    std::cout << "1. Search by ID\n";
    std::cout << "2. Search by Name\n";
    std::cout << "Enter choice: ";

    int choice;
    if (!(std::cin >> choice)) { clearInput(); return; }
    clearInput();

    if (choice == 1) {
        int id;
        std::cout << "Enter Student ID: ";
        if (!(std::cin >> id)) { clearInput(); return; }
        clearInput();

        bool found = false;
        for (const auto& s : students) {
            if (s.id == id) {
                printHeader();
                printStudent(s);
                printDivider();
                found = true;
                break;
            }
        }
        if (!found) std::cout << "[Info] No student found with ID " << id << ".\n";

    } else if (choice == 2) {
        char query[50];
        std::cout << "Enter Name (or partial): ";
        std::cin.getline(query, 50);

        bool found = false;
        printHeader();
        for (const auto& s : students) {
            // Case-insensitive substring search
            std::string sName(s.name), q(query);
            std::transform(sName.begin(), sName.end(), sName.begin(), ::tolower);
            std::transform(q.begin(),    q.end(),    q.begin(),    ::tolower);
            if (sName.find(q) != std::string::npos) {
                printStudent(s);
                found = true;
            }
        }
        if (!found) {
            std::cout << "No student found matching \"" << query << "\".\n";
        }
        printDivider();
    } else {
        std::cout << "[Error] Invalid choice.\n";
    }
}

void updateStudent() {
    std::vector<Student> students = loadStudents();

    if (students.empty()) {
        std::cout << "\nNo records to update.\n";
        return;
    }

    std::cout << "\n=== Update Student Record ===\n";
    std::cout << "Enter Student ID to update: ";
    int id;
    if (!(std::cin >> id)) { clearInput(); return; }
    clearInput();

    for (auto& s : students) {
        if (s.id == id) {
            std::cout << "Current record:\n";
            printHeader();
            printStudent(s);
            printDivider();

            std::cout << "\nEnter new details (press Enter to keep current value):\n";

            // Name
            char buf[50];
            std::cout << "New Name [" << s.name << "]: ";
            std::cin.getline(buf, 50);
            if (strlen(buf) > 0) strncpy(s.name, buf, 50);

            // Course
            std::cout << "New Course [" << s.course << "]: ";
            std::cin.getline(buf, 50);
            if (strlen(buf) > 0) strncpy(s.course, buf, 50);

            // Age
            std::cout << "New Age [" << s.age << "]: ";
            std::cin.getline(buf, 50);
            if (strlen(buf) > 0) {
                int newAge = atoi(buf);
                if (newAge > 0 && newAge < 150) s.age = newAge;
                else std::cout << "[Warning] Invalid age — keeping original.\n";
            }

            // GPA
            std::cout << "New GPA [" << std::fixed << std::setprecision(2) << s.gpa << "]: ";
            std::cin.getline(buf, 50);
            if (strlen(buf) > 0) {
                float newGpa = static_cast<float>(atof(buf));
                if (newGpa >= 0.0f && newGpa <= 4.0f) s.gpa = newGpa;
                else std::cout << "[Warning] Invalid GPA — keeping original.\n";
            }

            saveStudents(students);
            std::cout << "[Success] Record updated.\n";
            return;
        }
    }

    std::cout << "[Info] No student found with ID " << id << ".\n";
}

void deleteStudent() {
    std::vector<Student> students = loadStudents();

    if (students.empty()) {
        std::cout << "\nNo records to delete.\n";
        return;
    }

    std::cout << "\n=== Delete Student Record ===\n";
    std::cout << "Enter Student ID to delete: ";
    int id;
    if (!(std::cin >> id)) { clearInput(); return; }
    clearInput();

    auto it = std::find_if(students.begin(), students.end(),
                           [id](const Student& s) { return s.id == id; });

    if (it == students.end()) {
        std::cout << "[Info] No student found with ID " << id << ".\n";
        return;
    }

    std::cout << "Record to delete:\n";
    printHeader();
    printStudent(*it);
    printDivider();

    std::cout << "Are you sure you want to delete this record? (y/n): ";
    char confirm;
    std::cin >> confirm;
    clearInput();

    if (confirm == 'y' || confirm == 'Y') {
        students.erase(it);
        saveStudents(students);
        std::cout << "[Success] Record deleted.\n";
    } else {
        std::cout << "[Cancelled] Record was not deleted.\n";
    }
}

void displayMenu() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║    STUDENT MANAGEMENT SYSTEM         ║\n";
    std::cout << "╠══════════════════════════════════════╣\n";
    std::cout << "║  1. Add Student                      ║\n";
    std::cout << "║  2. Display All Students             ║\n";
    std::cout << "║  3. Search Student                   ║\n";
    std::cout << "║  4. Update Student                   ║\n";
    std::cout << "║  5. Delete Student                   ║\n";
    std::cout << "║  6. Exit                             ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
    std::cout << "Enter your choice: ";
}
