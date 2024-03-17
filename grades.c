#define _POSIX_C_SOURCE 200809L // For <string.h> (strdup command)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Bool
#include "grades.h"
#include "linked-list.h"

typedef struct student {
    struct list* courses; // List of courses for each student
    char* name;
    int id;
} student_t;

typedef struct course {
    char* name; // Name of course
    int grade; // Grade of course
} course_t;

typedef struct grades {
    struct list* students;
} grades_t;

static void destroy_student(void* data) {
    student_t* st = (student_t*)data;
    if (st == NULL) return;
    list_destroy(st->courses);
    free(st->name);
    free(st);
    return;
};

static void destroy_course(void* data) {
    course_t* crs = (course_t*)data;
    if (crs == NULL) return;
    free(crs->name);
    free(crs);
};

static int clone_course(void* data, void** output) {
    course_t* crs = (course_t*)data;
    course_t* new_crs = (course_t*)malloc(sizeof(course_t));
    if (new_crs == NULL) return -1; // Fail
    new_crs->name = strdup(crs->name);
    if (new_crs->name == NULL) {
        free(new_crs);
        return -1; // Fail
    }
    new_crs->grade = crs->grade;
    *output = new_crs;
    return 0;
};


static int clone_student(void* data, void** output) {
    student_t* st = (student_t*)data;
    if (st == NULL) return -1;
    // creating new_st and relevant fields
    student_t* new_st = (student_t*)malloc(sizeof(student_t));
    if (new_st == NULL) return -1; // Fail
    new_st->name = strdup(st->name);
    if (new_st->name == NULL) {
        free(new_st);
        return -1; // Fail
    }
    new_st->id = st->id;
    new_st->courses = list_init(clone_course, destroy_course);
  
    if (new_st->courses == NULL) {
        free(new_st->name);
        free(new_st);
        return -1; // Fail
    }

    // copying each course
    struct iterator* crs_it = list_begin(st->courses);
    while (crs_it != list_end(st->courses)) {
        course_t* crs = (course_t*)list_get(crs_it);
        course_t* new_crs = (course_t*)malloc(sizeof(course_t));
        if (new_crs == NULL) {
            list_destroy(new_st->courses);
            free(new_st->name);
            free(new_st);
            return -1; // Fail
        }
        new_crs->name = strdup(crs->name);
        if (new_crs->name == NULL) {
            list_destroy(new_st->courses);
            free(new_st);
            return -1; // Fail 
        }
        new_crs->grade = crs->grade; 
        list_push_back(new_st->courses, new_crs);
        crs_it = list_next(crs_it);
    };
    *output = new_st;
    return 0;
};


static struct student* find_student(struct grades *grades, int id) {
    if (grades == NULL || grades->students == NULL) return NULL;
    struct iterator* curr_it_st = list_begin(grades->students);
    // No need to check for error. if curr_it is null, then 
    // we would skip loop
    
    // find student with id
    while (curr_it_st) {
        struct student* curr_st = list_get(curr_it_st);
        if (curr_st->id == id) {
            return curr_st; 
        }
        curr_it_st = list_next(curr_it_st);
    };
    return NULL;
};

struct grades* grades_init() {
    struct grades* grades = (struct grades*)malloc(sizeof(struct grades));
    if (grades == NULL) return NULL;
    // Students list
    grades->students = list_init(clone_student, destroy_student); 
    if (grades->students == NULL) {
        free(grades);
        return NULL;
    }
    return grades;
};


void grades_destroy(struct grades *grades) {
    if (grades == NULL) return;
    list_destroy(grades->students);
    free(grades);
};


int grades_add_student(struct grades *grades, const char *name, int id) {
    // Every student is a list of courses
    if (grades == NULL || name == NULL || grades->students == NULL) return -1;

    // Enter student in relevant place
    struct iterator *curr_st_it = list_begin(grades->students);
    
    while (curr_st_it) {
        student_t* curr_st = (student_t*)list_get(curr_st_it); 
        if (curr_st->id == id){
            return -1; // Fail. student exists
        }
        curr_st_it = list_next(curr_st_it);
    };

    struct student new_st;
    new_st.id = id;
    // Copy name
    new_st.name = (char*)name;
    new_st.courses = list_init(clone_course, destroy_course);
    if (!new_st.courses) return -1; // Fail
    int res;
    res = list_push_back(grades->students, &new_st);
    if (res != 0) return -1; // Fail
    free(new_st.courses); // list_push_back holds a copy
    return 0; // Success
};

int grades_add_grade(struct grades *grades, const char *name, int id, 
    int grade) {
                if (grades == NULL || grades->students == NULL || name == NULL){
                    return -1; // Fail
                };
                if (grade < 0 || grade > 100) return -1; // Fail 
                struct student* curr_st = find_student(grades, id);
                if (curr_st == NULL) return -1; // Fail. No student found
                // search if course already exists
                struct iterator* curr_it = list_begin(curr_st->courses);
                // No need to check for error. if curr_it is null, then 
                // we would skip loop
                
                while (curr_it) {
                    struct course* curr_course = list_get(curr_it);
                    if (strcmp(curr_course->name, name) == 0) { 
                        return -1; // Fail, course exists
                    }
                    curr_it = list_next(curr_it);
                };
                // Create course
                struct course crs;
                // Copy
                crs.name = (char*)name;
                crs.grade = grade; // Add grade

                // list_insert returns 0 for success
                return list_push_back(curr_st->courses, &crs);
};

float grades_calc_avg(struct grades *grades, int id, char **out) {
    if (grades == NULL || grades->students == NULL) return -1; // Fail

    // Find student
    struct student* curr_st = find_student(grades,id);
    if (curr_st == NULL) return -1; // Fail

    *out = strdup(curr_st->name);

    struct iterator* curr_crs_it = list_begin(curr_st->courses);
    // No need to check for error. if curr_it is null, then 
    // we would skip loop
    float sum = 0;
    float n = 0;
    float avg = 0;
    while (curr_crs_it) {
        struct course* curr_crs = list_get(curr_crs_it);
        sum+=curr_crs->grade;
        n+=1;
        curr_crs_it = list_next(curr_crs_it);
    };
    if (n > 0) {avg = sum/n;}
    return avg;
};

static int print_student(struct student *st) {
    if (st == NULL) return -1; // Fail.
    struct iterator* crs_it = list_begin(st->courses);
    printf("%s %d:", st->name, st->id);
    bool first = true;
    while (crs_it) {
        struct course* crs = list_get(crs_it);
        if (!first){
            printf(", ");
        } else {
            printf(" ");
            first = false;
        }
        printf("%s %d", crs->name, crs->grade);
        crs_it = list_next(crs_it);
    }
    printf("\n");
    return 0;
};

int grades_print_student(struct grades *grades, int id) {
    if (grades == NULL || grades->students == NULL) return -1;
    struct student* st = find_student(grades, id);
    if (st == NULL) return -1; // Fail
    return print_student(st);
};

int grades_print_all(struct grades *grades) {
    if (grades == NULL || grades->students == NULL) return -1; // Fail
    struct iterator* st_it = list_begin(grades->students);

    while (st_it) {
        struct student* st = list_get(st_it);
        if (print_student(st) != 0 ) return -1; // Fail
        // Next
        st_it = list_next(st_it);
    };
    return 0; // success
};

