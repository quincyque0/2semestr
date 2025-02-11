#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define N2 100

void selectSort(int arr[], int n, int *comparisons, int *swaps) {
    int i, j, min_idx, temp;

    *comparisons = 0;
    *swaps = 0;

    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            (*swaps)+=3;
        }
        // temp = arr[i];
        // arr[i] = arr[min_idx];
        // arr[min_idx] = temp;
        // (*swaps)+=3;
    }
}


int* Filllne(int begin,int size,int *massive){
    for(int i =0; i<size;i++){
        massive[i]=begin + i;
    }
    return massive;

}


int* FillDie(int begin,int size,int *massive){
    for(int i =0; i<size;i++){
        massive[i]=begin -i;
    }
    return massive;

}
int checkSum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

int* FillRand(int size,int *massive){
    for(int i =0; i<size;i++){
        massive[i]=rand();
    }
    return massive;

}

int runNumber(int arr[], int n) {
    int series = 1;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i+1])
            series++;
    }
    return series;
}

int main() {
    int *arr = (int*)malloc(sizeof(int)*N);
    int n = N2;
    Filllne(1,n,arr);
    int comparisons, swaps, check_sum, runs;
    printf("Исходный массив: ");
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    check_sum = checkSum(arr, n);
    runs = runNumber(arr, n);



    selectSort(arr, n, &comparisons, &swaps);

    printf("Отсортированный массив: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Контрольная сумма: %d\n", checkSum(arr, n));
    printf("Число серий: %d\n", runNumber(arr, n));

    printf("Фактическое количество сравнений: %d\n", comparisons);
    printf("Фактическое количество переcтановок: %d\n", swaps);
    printf("Трудоёмкость сортировки(T) = %d \n",swaps + comparisons);

    
    int theoretical_comparisons = (n*n-n)/2;
    int theoretical_swaps = 3*(n - 1);  

    printf("Теоретическое количество сравнений: %d\n", theoretical_comparisons);
    printf("Теоретическое количество переcтановок: %d\n", theoretical_swaps);\
    printf("Теоретическая трудоёмкость сортировки(T) = %d \n\n",theoretical_swaps + theoretical_comparisons);
    printf("=============================================================\n\n");
    // второй вариант
    FillDie(n,n,arr);

    printf("Исходный массив: ");
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    check_sum = checkSum(arr, n);
    runs = runNumber(arr, n);

    

    selectSort(arr, n, &comparisons, &swaps);

    printf("Отсортированный массив: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Контрольная сумма: %d\n", checkSum(arr, n));
    printf("Число серий: %d\n", runNumber(arr, n));

    printf("Фактическое количество сравнений: %d\n", comparisons);
    printf("Фактическое количество переcтановок: %d\n", swaps);
    printf("Трудоёмкость сортировки(T) = %d \n",swaps + comparisons);

    printf("Теоретическое количество сравнений: %d\n", theoretical_comparisons);
    printf("Теоретическое количество переcтановок: %d\n", theoretical_swaps);
    printf("Теоретическая трудоёмкость сортировки(T) = %d \n\n",theoretical_swaps + theoretical_comparisons);
    // третий элемент
    printf("=============================================================\n\n");
    FillRand(n,arr);

    printf("Исходный массив: ");
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    check_sum = checkSum(arr, n);
    runs = runNumber(arr, n);



    selectSort(arr, n, &comparisons, &swaps);

    printf("Отсортированный массив: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Контрольная сумма: %d\n", checkSum(arr, n));
    printf("Число серий: %d\n", runNumber(arr, n));

    printf("Фактическое количество сравнений: %d\n", comparisons);
    printf("Фактическое количество переcтановок: %d\n", swaps);
    printf("Трудоёмкость сортировки(T) = %d \n",swaps + comparisons);

    printf("Теоретическое количество сравнений: %d\n", theoretical_comparisons);
    printf("Теоретическое количество переcтановок: %d\n", theoretical_swaps);
    printf("Теоретическая трудоёмкость сортировки(T) = %d \n\n",theoretical_swaps + theoretical_comparisons);



    
}