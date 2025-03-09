#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define N2 100

void Copy(int* arr1 , int* arr2,int size){
    for(int i =0 ; i < size;i++){
        arr1[i] = arr2[i];
    }
}
void selectSortBase(int arr[], int n, int *comparisons, int *swaps) {
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


        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
        (*swaps)+=3;
    }
}
void selectSortGrade(int arr[], int n, int *comparisons, int *swaps) {
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
void Tablic(int A,int B, int C, int D,int E, int F,int A1,int B1, int C1, int D1,int E1, int F1,int TT , int CC,int CC2 , int TT2){
    printf("N\t\tM+C\t\tисх(убыв)\tисх(случ)\tисх(воз)\tул(убыв)\tул(случ)\tул(воз)\n");
    printf("10\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",CC+TT,A,B,C,D,E,F);
    printf("100\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",CC2+TT2,A1,B1,C1,D1,E1,F1);

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
        massive[i]=rand()%10000000;
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
    int *arr2 = (int*)malloc(sizeof(int)*N);
    int *arr1 = (int*)malloc(sizeof(int)*N);
    
    int n = N;
    int n2 =N2;
    Filllne(1,n,arr2);
    Copy(arr1,arr2,N);
    int comparisons, swaps, check_sum, runs;




    printf("Исходный массив: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr1[i]);
    printf("\n");
    

    check_sum = checkSum(arr1, n);
    runs = runNumber(arr1, n);

    selectSortBase(arr1, n, &comparisons, &swaps);
    int C = swaps + comparisons;
    printf("Отсортированный массив: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr1[i]);
    printf("\n");
    Filllne(1,n,arr2);
    selectSortGrade(arr1, n, &comparisons, &swaps);
    int F = swaps + comparisons;
    Filllne(1,n,arr2);
    selectSortBase(arr1, n2, &comparisons, &swaps);
    int C1 = swaps + comparisons;
    Filllne(1,n,arr2);
    selectSortGrade(arr1, n2, &comparisons, &swaps);
    int F1 = swaps + comparisons;
    Filllne(1,n,arr2);

    

    printf("Контрольная сумма: %d\n", checkSum(arr1, n));
    printf("Число серий: %d\n", runNumber(arr1, n));

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
    FillDie(n,n,arr1);

    printf("Исходный массив: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr1[i]);
    printf("\n");

    selectSortBase(arr1, n, &comparisons, &swaps);
    int A = swaps + comparisons;
    printf("Отсортированный массив: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr1[i]);
    printf("\n");
    FillDie(n,n,arr1);
    selectSortGrade(arr1, n, &comparisons, &swaps);
    int D = swaps + comparisons;
    FillDie(n,n,arr1);
    selectSortBase(arr1, n2, &comparisons, &swaps);
    int A1 = swaps + comparisons;
    FillDie(n,n,arr1);
    selectSortGrade(arr1, n2, &comparisons, &swaps);
    int D1 = swaps + comparisons;
    FillDie(n,n,arr1);
    int theoretical_comparisons2 = (n2*n2-n2)/2;
    int theoretical_swaps2 = 3*(n2- 1);  

    check_sum = checkSum(arr1, n);
    runs = runNumber(arr1, n);

    

    selectSortBase(arr1, n, &comparisons, &swaps);


    printf("Контрольная сумма: %d\n", checkSum(arr1, n));
    printf("Число серий: %d\n", runNumber(arr1, n));

    printf("Фактическое количество сравнений: %d\n", comparisons);
    printf("Фактическое количество переcтановок: %d\n", swaps);
    printf("Трудоёмкость сортировки(T) = %d \n",swaps + comparisons);

    printf("Теоретическое количество сравнений: %d\n", theoretical_comparisons);
    printf("Теоретическое количество переcтановок: %d\n", theoretical_swaps);
    printf("Теоретическая трудоёмкость сортировки(T) = %d \n\n",theoretical_swaps + theoretical_comparisons);
    
    // третий элемент
    printf("=============================================================\n\n");
    FillRand(n,arr1);

    printf("Исходный массив: ");
    
    selectSortBase(arr1, n, &comparisons, &swaps);
    int B = swaps + comparisons;

    printf("Отсортированный массив: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr1[i]);
    printf("\n");
    FillRand(n,arr1);
    selectSortGrade(arr1, n, &comparisons, &swaps);
    int E = swaps + comparisons;
    FillRand(n,arr1);
    selectSortBase(arr1, n2, &comparisons, &swaps);
    int B1 = swaps + comparisons;
    FillRand(n,arr1);
    selectSortGrade(arr1, n2, &comparisons, &swaps);
    int E1 = swaps + comparisons;
    FillRand(n,arr1);

    check_sum = checkSum(arr1, n);
    runs = runNumber(arr1, n);

    selectSortBase(arr1, n, &comparisons, &swaps);

    printf("Отсортированный массив: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr1[i]);
    printf("\n");

    printf("Контрольная сумма: %d\n", checkSum(arr1, n));
    printf("Число серий: %d\n", runNumber(arr1, n));

    printf("Фактическое количество сравнений: %d\n", comparisons);
    printf("Фактическое количество переcтановок: %d\n", swaps);
    printf("Трудоёмкость сортировки(T) = %d \n",swaps + comparisons);

    printf("Теоретическое количество сравнений: %d\n", theoretical_comparisons);
    printf("Теоретическое количество переcтановок: %d\n", theoretical_swaps);
    printf("Теоретическая трудоёмкость сортировки(T) = %d \n\n",theoretical_swaps + theoretical_comparisons);

    Tablic(A,B,C,D,E,F,A1,B1,C1,D1,E1,F1,theoretical_comparisons,theoretical_swaps,theoretical_comparisons2,theoretical_swaps2);


    
}