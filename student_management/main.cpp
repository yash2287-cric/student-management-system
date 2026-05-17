#include "operations.h"
#include <iostream>
#include <limits>

int main() {
    int choice;

    std::cout << "Welcome to the Student Management System\n";

    while (true) {
        displayMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[Error] Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: addStudent();        break;
            case 2: displayAllStudents(); break;
            case 3: searchStudent();     break;
            case 4: updateStudent();     break;
            case 5: deleteStudent();     break;
            case 6:
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "[Error] Invalid choice. Please select 1-6.\n";
        }
    }

    return 0;
}
