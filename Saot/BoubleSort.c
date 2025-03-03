#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int* Filllne(int begin,int size,int *massive){
    for(int i = 0; i < size; i++){
        massive[i] = begin + i;
    }
    return massive;
}

int* FillDie(int begin,int size,int *massive){
    for(int i = 0; i < size ;i++){
        massive[i] = begin - i;
    }
    return massive;
}

void Printer(int *arr, int size){
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int* FillRand(int size, int *massive){
    for(int i = 0; i < size; i++){
        massive[i] = rand() % 10000000;
    }
    return massive;
}

void Tablic(int *Tablic){
    printf("N\t\tM+C\t\tисх(убыв)\tисх(случ)\tисх(воз)\n");
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[0],Tablic[1],Tablic[2],Tablic[3],Tablic[4]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[5],Tablic[6],Tablic[7],Tablic[8],Tablic[9]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[10],Tablic[11],Tablic[12],Tablic[13],Tablic[14]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[15],Tablic[16],Tablic[17],Tablic[18],Tablic[19]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[20],Tablic[21],Tablic[22],Tablic[23],Tablic[24]);
}
void Tablic_Add(int *cur, int *tablic, int A,int B,int C,int D,int E){
    tablic[*cur] = A;
    tablic[*cur+1] = B;
    tablic[*cur+2] = C;
    tablic[*cur+3] = D;
    tablic[*cur+4] = E;
    *cur += 5;
}

void boubleSort(int *arr, int size, int *comparisons, int *swaps){
    int tmp;
    *comparisons = 0;
    *swaps = 0;
    for(int i = 0; i < size - 1; i++){
        for(int j = size - 1; j > i; j--){
            (*comparisons)++; if(arr[j] < arr[j-1]){
                tmp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = tmp;
                (*swaps) += 3;
            }
        }
    }
}

int main(){
    int N = 100;
    int *A = (int*)malloc(sizeof(int) * 500);
    int *Tablic_Znach = (int*)malloc(sizeof(int) * 25);
    int comparisons, swaps ,cur = 0;
    
    for(int N = 100; N <= 500 ; N += 100 ){
        int theoretical_swaps_orderly = 0;
        int theoretical_swaps_random = 3* ((N * N) - N) / 4;
        int theoretical_comparisons = ((N * N) - N) / 2;
        int theoretical_swaps_notorderly = ((N * N) - N) / 2;

        FillDie(N, N , A);
        // printf("Исходный массив: ");
        // Printer(A, N);
        boubleSort(A, N, &comparisons, &swaps);
        // printf("Отсортированный массив: ");
        // Printer(A, N);
        printf("N : %d",N);
        printf("Теоретическое количество сравнений(%d), перестановок (%d)\n", theoretical_comparisons, theoretical_swaps_notorderly);
        printf("Фактическое количество сравнений: %d\n", comparisons);
        printf("Фактическое количество переcтановок: %d\n", swaps);
        printf("Трудоёмкость сортировки(T) = %d \n\n",swaps + comparisons);
        int sortDOWN = comparisons+swaps;
        

        Filllne(1, N , A);
        // printf("Исходный массив: ");
        // Printer(A, N);
        boubleSort(A, N, &comparisons, &swaps);
        // printf("Отсортированный массив: ");
        // Printer(A, N);
        printf("N : %d",N);
        printf("Теоретическое количество сравнений(%d), перестановок (%d)\n", theoretical_comparisons, theoretical_swaps_orderly);
        printf("Фактическое количество сравнений: %d\n", comparisons);
        printf("Фактическое количество переcтановок: %d\n", swaps);
        printf("Трудоёмкость сортировки(T) = %d \n\n",swaps + comparisons);
        int sortUP = comparisons+swaps;

        FillRand(N , A);
        // printf("Исходный массив: ");
        // Printer(A, N);
        boubleSort(A, N, &comparisons, &swaps);
        // printf("Отсортированный массив: ");
        // Printer(A, N);
        printf("N : %d",N);
        printf("Теоретическое количество сравнений(%d), перестановок(Ср) (%d)\n", theoretical_comparisons, theoretical_swaps_random);
        printf("Фактическое количество сравнений: %d\n", comparisons);
        printf("Фактическое количество переcтановок: %d\n", swaps);
        printf("Трудоёмкость сортировки(T) = %d \n\n",swaps + comparisons);
        int sortRAND = comparisons+swaps;

        Tablic_Add(&cur,Tablic_Znach,N,theoretical_comparisons+theoretical_swaps_random,sortDOWN,sortRAND,sortUP);

    }
    
    Tablic(Tablic_Znach);
}