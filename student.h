#ifndef STUDENT_H
#define STUDENT_H

struct Student {
    char *name;
    int age;
    int id;
};

struct Student* student_clone(struct Student* st);
void student_destroy(struct Student* st);
void student_print(struct Student* st);

#endif