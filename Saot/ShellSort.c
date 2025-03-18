#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

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

void Tablic_Add4(int *cur, char **Ctablic, char *A, char *B, char *C, char *D) {
    Ctablic[*cur] = A;
    Ctablic[*cur + 1] = B;
    Ctablic[*cur + 2] = C;
    Ctablic[*cur + 3] = D;
    *cur += 4;
}

char* stroker(int* numbers, int size) {
    char *str = (char*)malloc(100 * sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    str[0] = '\0';
    char temp[20];

    for (int i = 0; i < size; i++) {
        snprintf(temp, sizeof(temp), "%d", numbers[i]);
        strcat(str, temp);

        if (i < size - 1) {
            strcat(str, " ");
        }
    }

    return str;
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

void insertSort( int A[],int n, int *ptr_cf, int *ptr_mf){
    *ptr_mf = 0;
    *ptr_cf = 0;

    for(int i = 1; i < n; i++){
        int t = A[i];
        int j = i - 1;
        (*ptr_mf)++;
        while(j >= 0){
            (*ptr_cf)++;
            if(t < A[j]){
                A[j+1] = A[j];
                (*ptr_mf)++;
                j--;
            }else break;
        }
        A[j+1] = t;
        (*ptr_mf)++;
    }
} 

int* FillH(int h[], int m) {
    h[0] = 1;
    for (int i = 1; i < m; i++) {
        h[i] = h[i - 1] * 3 + 1;
    }
    return h;
}

int* ShellSort(int arr[], int n, int *comparasions, int *swaps, int *razM) {
    *comparasions = 0;
    *swaps = 0;

    int m = log(n) / log(2) - 3;
    if (m < 1) m = 1;
    *razM = m;
    int *h = (int*)malloc(m * sizeof(int));
    if (h == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    FillH(h, m);

    for (; m > 0; m--) {
        int k = h[m - 1];
        for (int i = k; i < n; i++) {
            int t = arr[i];
            (*swaps)++;
            int j = i - k;
            while (j >= 0) {
                (*comparasions)++;
                if (t < arr[j]) {
                    arr[j + k] = arr[j];
                    (*swaps)++;
                    j = j - k;
                } else break;
                arr[j + k] = t;
                (*swaps)++;
            }
        }
    }
    return h;
}

void Tablic(char **Tablic) {
    printf("%-10s%-30s%-15s%-15s\n", "N", "h1 … hm по формуле Д.Кнута", "   Insert", "    Shell");
    for (int i = 0; i < 5; i++) { 
        printf("%-10s%-30s%-15s%-15s\n", Tablic[i * 4], Tablic[i * 4 + 1], Tablic[i * 4 + 2], Tablic[i * 4 + 3]);
    }
}

int main() {
    int N = 100;
    srand(time(NULL));
    int *A = (int*)malloc(sizeof(int) * 500);
    if (A == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    char **Tablic_Znach = (char**)malloc(sizeof(char*) * 20);
    if (Tablic_Znach == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(A);
        return 1;
    }
    int comparisons, swaps, cur = 0, m;
    int *Steps;

    for (int N = 100; N <= 500; N += 100) {
        FillRand(N, A);
        Steps = ShellSort(A, N, &comparisons, &swaps, &m);
        char *shellStr = strokernumb(comparisons + swaps);
        char *strokeStr = stroker(Steps, m);
        FillRand(N, A);
        insertSort(A, N, &comparisons, &swaps);
        char *insertStr = strokernumb(comparisons + swaps);
        Tablic_Add4(&cur, Tablic_Znach, strokernumb(N), strokeStr, insertStr, shellStr);

        free(Steps);
        free(shellStr);
        free(strokeStr);
        free(insertStr);
    }

    Tablic(Tablic_Znach);

    free(A);
    for (int i = 0; i < 20; i++) {
        if (Tablic_Znach[i] != NULL) {
            free(Tablic_Znach[i]);
        }
    }
    free(Tablic_Znach);

    return 0;
}