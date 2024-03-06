#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

struct Student* student_clone(struct Student* st) { // Clone the student
    if (st == NULL) return 1;
    char *name_copy = st->name;
    int age_copy = st->age;
    int id_copy = st->id;
    struct Student* st_clone = (struct Student*)malloc(sizeof(struct Student));
    if (st_clone == NULL) return 1;
    st_clone->name = name_copy;
    st_clone->age = age_copy;
    st_clone->id = id_copy;
};

void student_destroy(struct Student* st) { // Free memory of student
    if (st == NULL) return 1;
    free(st->name);
    // No need to free the other variables as they are not pointers
    free(st);
};

void student_print(struct Student* st) {
    if (st == NULL) return 1;
    printf("student name: %s, age: %d, id: %d.\n", st->name, st->age, st->id);
}