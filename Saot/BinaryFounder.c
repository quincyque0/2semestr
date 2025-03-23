#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int* Filllne(int begin, int size, int *massive) {
    for (int i = 0; i < size; i++) {
        massive[i] = begin + i;
    }
    return massive;
}

char* strokernumb(int number) {
    char *str = (char*)malloc(10 * sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    snprintf(str, 10, "%d", number);
    return str;
}

void Tablic(char **Tablic) {
    printf(" %-7s%-15s%-15s\n", "N", "Сф  I версия", "   Сф  II версия");
    for (int i = 0; i < 10; i++) {
        printf("%-10s  %-15s  %-15s\n", Tablic[i * 3], Tablic[i * 3 + 1], Tablic[i * 3 + 2]);
    }
}

void Tablic_Add3(int *cur, char **Ctablic, char *A, char *B, char *C) {
    Ctablic[*cur] = A;
    Ctablic[*cur + 1] = B;
    Ctablic[*cur + 2] = C;
    *cur += 3;
}

int binaryFounder(int *arr, int size, int *comporsions, int *moves, int x) {
    *comporsions = 0;
    *moves = 0;
    int m;

    int L = 0, R = size - 1; 
    while (L <= R) { 
        m = (L + R) / 2;
        (*comporsions)++;
        if (arr[m] == x) {
            return m;
        }
        (*comporsions)++;
        if (arr[m] < x) {
            L = m + 1;
        } else {
            R = m - 1;
        }
    }
    return -1; 
}
int binaryFounderGRADE(int *arr, int size, int *comparisons, int *moves, int x) {
    *comparisons = 0;
    *moves = 0;

    int L = 0, R = size - 1, m;

    while (L <= R) {
        m = (L + R) / 2;
        (*comparisons)++;

        if (arr[m] == x) {
            return m;
        } else if (arr[m] < x) {
            L = m + 1; 
        } else {
            R = m - 1;
        }
    }

    return -1; 
}

int main() {
    printf("enter number for search");
    int input;
    scanf("%d",&input);
    int N = 100;
    srand(time(NULL));
    int *A = (int*)malloc(sizeof(int) * 1000);
    if (A == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char **Tablic_Znach = (char**)malloc(sizeof(char*) * 30);
    if (Tablic_Znach == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(A);
        return 1;
    }

    int comparisons = 0, swaps = 0, cur = 0;

    for (int i = N; i <= 1000; i += 100) {
        Filllne(0, i, A);
        int O = binaryFounder(A, i, &comparisons, &swaps, 2);
        char *chis1 = strokernumb(i); 
        char *chis3 = strokernumb(comparisons);
        int OO = binaryFounderGRADE(A, i, &comparisons, &swaps,2);
        char *chis2 = strokernumb(comparisons);
        Tablic_Add3(&cur, Tablic_Znach, chis1, chis3, chis2);
    }

    Tablic(Tablic_Znach);


    free(A);
    for (int i = 0; i < 30; i++) {
        if (Tablic_Znach[i] != NULL) {
            free(Tablic_Znach[i]);
        }
    }
    free(Tablic_Znach);

}