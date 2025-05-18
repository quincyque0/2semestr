#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char stud_name[64];
    unsigned int math_score;
    unsigned int phys_score;
    unsigned int cs_score;
    unsigned int total_score;
} Student;

// Прототипы функций
Student create_student(const char* name, unsigned int math, 
                      unsigned int phys, unsigned int cs);
void calculate_total(Student* student);

int compare_by_total(Student a, Student b);
int compare_by_physics(Student a, Student b);

void insertion_sort(Student* array, size_t size, int (*compare)(Student, Student));
void quick_sort(Student* array, size_t size, int (*compare)(Student, Student));
void counting_sort(Student* array, size_t size);
void bogo_sort(Student* array, size_t size, int (*compare)(Student, Student));

#endif // SORTING_H