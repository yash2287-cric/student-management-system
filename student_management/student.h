#ifndef STUDENT_H
#define STUDENT_H

// Student record structure stored in binary file
struct Student {
    int  id;
    char name[50];
    char course[50];
    float gpa;
    int  age;
};

#endif // STUDENT_H
