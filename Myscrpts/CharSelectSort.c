#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

char* FillRand(int size, char *massive) {
    char ascii[26] = "rudometow";
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        massive[i] = ascii[rand() % 26];
    }
    massive[size] = '\0';
    return massive;
}

void Printer(char *massive, int size){
    for (int i = 0; i < size; i++) {
        printf("%c", massive[i]); 
    }
    printf("\n");
}

void selectionSort(char* arr, int n) { 
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (int i = 0; i < n - 1; i++) { 
        int min_idx = i; 
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) { 
            char temp = arr[i]; 
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Selection sort time: %f seconds\n", cpu_time_used);
}

int main() {
    char A[] = "rudometow"; 
    FillRand(N, A);
    printf("Original array: ");
    Printer(A, N);
    printf("\n");

    selectionSort(A, N); 
    printf("Sorted array: ");
    Printer(A, N);
    printf("\n");

    return 0;
}