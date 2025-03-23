#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int runNumber(int array[], int size) {
    int serie = 1;
    int row = 1;
    for (int i = 0; i < size - 1; i++) {
        if (array[i] <= array[i+1]) {
            row += 1;
        }
        else if (array[i] >= array[i+1] && row > 0) {
            row = 1;
            serie += 1;
        }
    }
    return serie;
}

int* FillInc(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = i + 1;
    }
    return array;
}

int* FillDec(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = size - i;
    }
    return array;
}

int* FillRand(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = rand();
    }
    return array;
}

void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\t");
}

long int checkSum(int array[], int size) {
    long int total = 0;
    for(int i = 0; i < size; i++) {
        total += array[i];
    }
    return total;
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int InsertSort(int arr[], int n) {
    int Cf = 0;
    int Mf = 0;
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        Mf++;
        int j = i - 1;
        while (j >= 0) {
            Cf++;
            if (temp < arr[j]) {
                arr[j+1] = arr[j];
                Mf++;
                j = j - 1;
            }
            else break;
        }
        arr[j+1] = temp;
        Mf++;
    }
    return Cf + Mf;
}

int* FillH(int h[], int m) {
    h[0] = 1;
    for (int i = 1; i < m; i++) {
        h[i] = h[i-1]*3+1;
    }
    return h;
}

int ShellSort(int arr[], int n) {
    int m = log(n)/log(2)-3;
    int h[m];
    FillH(h, m);
    int Cf = 0;
    int Mf = 0;
    for (m; m > 0; m--) {
        int k = h[m-1];
        for (int i = k; i < n; i++) {
            int t = arr[i];
            Mf++;
            int j = i - k;
            while (j >= 0) {
                Cf++;
                if (t < arr[j]) {
                    arr[j+k] = arr[j];
                    Mf++;
                    j = j - k;
                }
                else break;
                arr[j+k] = t;
                Mf++;
            }
        }
    }
    return Cf+Mf;
}

void printInfo(int arr[], int n) {
    FillRand(arr, n);
    int diff = ShellSort(arr, n);
}void printTableInsertSort(int arr[]) {
    printf(" _________________________________________________________________\n");
    printf("|   N   | h1 ... hm по          | Insert Мф + Сф | Shell Мф + Сф |\n");
    printf("|       | формуле Д.Кнута       |                |               |\n");
    printf("|_______|_______________________|________________|_______________|\n");
    int N = 100;
    for (N; N <= 200; N += 100) {
        int m = log(N)/log(2)-2;
        int h[m];
        printf("|%d\t|", N);
        printArray(FillH(h, m), m);
        printf("\t|%d\t\t |%d\t\t |\n", InsertSort(FillRand(arr, N), N), ShellSort(FillRand(arr, N), N));
        printf("|_______|_______________________|________________|_______________|\n");
    }
    for (N; N <= 500; N += 100) {
        int m = log(N)/log(2)-2;
        int h[m];
        printf("|%d\t|", N);
        printArray(FillH(h, m), m);
        printf("|%d\t\t |%d\t\t |\n", InsertSort(FillRand(arr, N), N), ShellSort(FillRand(arr, N), N));
        printf("|_______|_______________________|________________|_______________|\n");
    }
}


void main() {
    srand(time(NULL));

    int n = 500;
    int arr[n];
    printInfo(arr, 100);
    printInfo(arr, 200);
    printInfo(arr, 300);
    printInfo(arr, 400);
    printInfo(arr, 500);

    printTableInsertSort(arr);

}