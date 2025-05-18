#include "sorting.h"

// Quick Sort — это алгоритм сортировки, который выбирает опорный элемент (так называемый "pivot")
// и рекурсивно сортирует элементы, разделяя массив на две части: элементы меньше опорного и
// элементы больше опорного, затем объединяет отсортированные части.

// https://upload.wikimedia.org/wikipedia/commons/6/6a/Sorting_quicksort_anim.gif

void _swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

// https://ru.wikipedia.org/wiki/%D0%91%D1%8B%D1%81%D1%82%D1%80%D0%B0%D1%8F_%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0#:~:text=5%5D%3A-,algorithm%20partition(A%2C%20low%2C%20high)%20is,-pivot%C2%A0%3A%3D%20A%5Bhigh
int __partition(Student list[], int low, int high, int (*func)(Student, Student)) {
    Student pivot = list[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (!func(list[j], pivot)) {
            i++;
            _swap(&list[i], &list[j]);
        }
    }
    
    _swap(&list[i + 1], &list[high]);
    return i + 1;
}

// https://ru.wikipedia.org/wiki/%D0%91%D1%8B%D1%81%D1%82%D1%80%D0%B0%D1%8F_%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0#:~:text=%D0%B2%D1%8B%D0%B3%D0%BB%D1%8F%D0%B4%D0%B8%D1%82%20%D1%81%D0%BB%D0%B5%D0%B4%D1%83%D1%8E%D1%89%D0%B8%D0%BC%20%D0%BE%D0%B1%D1%80%D0%B0%D0%B7%D0%BE%D0%BC%3A-,algorithm%20quicksort(A%2C%20low%2C%20high)%20is,-if%20low%20%3C%20high
void _quickSort(Student list[], int low, int high, int (*func)(Student, Student)) {
    if (low >= high) return;
        int pi = __partition(list, low, high, func);

        _quickSort(list, low, pi - 1, func); // до pi
        _quickSort(list, pi + 1, high, func); // после pi
}

// O(n*log(n))
void quickSort(Student list[], size_t N, int (*func)(Student, Student)) {
    _quickSort(list, 0, N - 1, func);
}