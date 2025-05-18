#include "sorting.h"

// Counting Sort — это алгоритм сортировки, который подсчитывает количество вхождений
// каждого уникального элемента в массиве, использует эти подсчёты для определения позиции
// каждого элемента в отсортированном массиве и размещает элементы на основе этих позиций.

// max O(n + k)
void сountingSort(Student list[], size_t N) {
    Student matrix[300 + 1][N]; // needs more memory, but retains full struct
    int C[300 + 1];
    memset(C, 0, sizeof(C));

    for (size_t i = 0; i < N; i++) {
        int score = list[i].total_score;
        matrix[score][C[score]++] = list[i];
    }

    size_t index = 0;
    for (int score = 300; score >= 0; score--)
        for (int j = 0; j < C[score]; j++)
            list[index++] = matrix[score][j];
}