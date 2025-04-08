#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int moves = 0;
int comparisons = 0;


int* Filllne(int begin, int size, int *massive) {
    for (int i = 0; i < size; i++) {
        massive[i] = begin + i;
    }
    return massive;
}


int* FillDie(int begin, int size, int *massive) {
    for (int i = 0; i < size; i++) {
        massive[i] = begin - i;
    }
    return massive;
}


void Printer(int *arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


int* FillRand(int size, int *massive) {
    for (int i = 0; i < size; i++) {
        massive[i] = rand() % 10000000;
    }
    return massive;
}


void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
    moves+=3;
}
void quickSortRecursive_V2(int *arr, int low, int high) {
    while (low < high) { 
        int x = arr[low], i = low, j = high;
        while (i <= j) {
            while (arr[i] < x) { i++; comparisons++; }
            while (arr[j] > x) { j--; comparisons++; }
            if (i <= j) {
                swap(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }
        
        if (j - low < high - i) {

            quickSortRecursive_V2(arr, low, j);
            low = i; 
        } else {

            quickSortRecursive_V2(arr, i, high);
            high = j; 
        }
    }
}
void quickSortRecursive(int *arr, int low, int high) {
    
    int x = arr[low], i = low, j = high;
    while (i <= j) {
        while (arr[i] < x) {
            i = i + 1;
            comparisons++;
        }
        while (arr[j] > x) {    
            j = j - 1;
            comparisons++;
        }
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i = i + 1;
            j = j - 1;
        }
    }
    if (low < j) {quickSortRecursive(arr, low, j);};
    if (i < high) {quickSortRecursive(arr, i, high);};
}


void quickSort(int arr[], int n) {
    moves = 0;
    comparisons = 0;

    quickSortRecursive(arr, 0, n - 1);
}
void quickSort_v2(int arr[], int n) {
    moves = 0;
    comparisons = 0;
    quickSortRecursive_V2(arr, 0, n - 1);
}


int ff, fd, fr;

int main() {
    srand(time(NULL));
    printf("------------------------------------------------------------------------------\n");
    printf("|   n  | quicksort(убывание) | quicksort(возрастание) | quicksort(случайный) |\n");
    printf("------------------------------------------------------------------------------\n");

    for (int n = 100; n <= 500; n += 100) {
        int *a = (int*)malloc(sizeof(int) * n);

   
        FillDie(n, n, a);
        quickSort(a, n);
        fd = moves + comparisons;

  
        FillRand(n, a);
        quickSort(a, n);
        fr = moves + comparisons;

     
        Filllne(0, n, a); 
        quickSort(a, n);
        ff = moves + comparisons;


        printf("| %4d | %-21d | %-21d | %-19d |\n", n, fd, ff, fr);
    }

    printf("------------------------------------------------------------------------------\n");

    printf("------------------------------------------------------------------------------\n");
    printf("|   n  | quicksort(убывание) | quicksort(возрастание) | quicksort(случайный) |\n");
    printf("------------------------------------------------------------------------------\n");

    for (int n = 100; n <= 500; n += 100) {
        int *a = (int*)malloc(sizeof(int) * n);

   
        FillDie(n, n, a);
        quickSort_v2(a, n);
        fd = moves + comparisons;

  
        FillRand(n, a);
        quickSort_v2(a, n);
        fr = moves + comparisons;

     
        Filllne(0, n, a); 
        quickSort_v2(a, n);
        ff = moves + comparisons;


        printf("| %4d | %-21d | %-21d | %-19d |\n", n, fd, ff, fr);
    }

    printf("------------------------------------------------------------------------------\n");



    return 0;
}