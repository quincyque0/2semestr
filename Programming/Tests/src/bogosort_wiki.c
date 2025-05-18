#include "sorting.h"

// Bogosort — неэффективный алгоритм сортировки, используемый только в образовательных целях и противопоставляемый
// другим, более реалистичным алгоритмам. Bogosort является частным случаем алгоритма Лас-Вегас.

void __swap(Student *a, Student *b) {
    Student tmp = *a;
    *a = *b;
    *b = tmp;
}

int _correct(Student arr[], int size, int (*func)(Student, Student)) {
    while (--size > 0)
        if (func(arr[size - 1], arr[size]))
            return 0;
    return 1;
}

void _shuffle(Student arr[], int size) {
    for (int i = 0; i < size; ++i)
        __swap(&arr[i], &arr[(rand() % size)]); 
}

void bogoSort(Student arr[], int size, int (*func)(Student, Student)) {
    while (!_correct(arr, size, func))
        _shuffle(arr, size);
}