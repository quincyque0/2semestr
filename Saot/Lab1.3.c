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
void Tablic_Add(int *cur, int *tablic, int A,int B,int C,int D,int E,int F,int G){
    tablic[*cur] = A;
    tablic[*cur+1] = B;
    tablic[*cur+2] = C;
    tablic[*cur+3] = D;
    tablic[*cur+4] = E;
    tablic[*cur+5] = F;
    tablic[*cur+6] = G;
    *cur += 7;
}

void Tablic(int *Tablic){
    printf("N\t\tbobисх(убыв)\tbobисх(случ)\tbobисх(воз)\tshaисх(убыв)\tshaисх(случ)\tshaисх(воз)\n");
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[0],Tablic[1],Tablic[2],Tablic[3],Tablic[4],Tablic[5],Tablic[6]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[7],Tablic[8],Tablic[9],Tablic[10],Tablic[11],Tablic[12],Tablic[13]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[14],Tablic[15],Tablic[16],Tablic[17],Tablic[18],Tablic[19],Tablic[20]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[21],Tablic[22],Tablic[23],Tablic[24],Tablic[25],Tablic[26],Tablic[27]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[28],Tablic[29],Tablic[30],Tablic[31],Tablic[32],Tablic[33],Tablic[34]);


}


void shakerSort(int *arr, int size,int *comparisons, int *swaps){
    int l = 0,r = size-1, k = size,tmp;
    *comparisons = 0;
    *swaps = 0;
    do{
        for(int i = r; i > l;i--){
            (*comparisons)++;if(arr[i] < arr[i-1]){
                tmp = arr[i];
                arr[i]=arr[i-1];
                arr[i-1]=tmp;
                k=i;
                (*swaps) += 3;

            }
        }
        l=k;
        for(int j = l; j < r;j++){
            (*comparisons)++;if(arr[j] >arr[j+1]){
                tmp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=tmp;
                k=j;
                (*swaps) += 3;

            }
        }
        r=k;

    }while(l<r);

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
    srand(time(NULL));
    int *A = (int*)malloc(sizeof(int) * 500);
    int *Tablic_Znach = (int*)malloc(sizeof(int) * 35);
    int comparisons, swaps ,cur = 0;
    
    for(int N = 100; N <= 500 ; N += 100 ){
        // ---------------boubleSort-----------------------


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
        int BsortDOWN = comparisons+swaps;
        

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
        int BsortUP = comparisons+swaps;

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
        int BsortRAND = comparisons+swaps;
        
        //-------------------shakerSort-----------------------------



        FillDie(N, N , A);
        // printf("Исходный массив: ");
        // Printer(A, N);
        shakerSort(A, N, &comparisons, &swaps);
        // printf("Отсортированный массив: ");
        // Printer(A, N);
        printf("N : %d",N);
        printf("Теоретическое количество сравнений(%d), перестановок (%d)\n", theoretical_comparisons, theoretical_swaps_notorderly);
        printf("Фактическое количество сравнений: %d\n", comparisons);
        printf("Фактическое количество переcтановок: %d\n", swaps);
        printf("Трудоёмкость сортировки(T) = %d \n\n",swaps + comparisons);
        int SsortDOWN = comparisons+swaps;
        

        Filllne(1, N , A);
        // printf("Исходный массив: ");
        // Printer(A, N);
        shakerSort(A, N, &comparisons, &swaps);
        // printf("Отсортированный массив: ");
        // Printer(A, N);
        printf("N : %d",N);
        printf("Теоретическое количество сравнений(%d), перестановок (%d)\n", theoretical_comparisons, theoretical_swaps_orderly);
        printf("Фактическое количество сравнений: %d\n", comparisons);
        printf("Фактическое количество переcтановок: %d\n", swaps);
        printf("Трудоёмкость сортировки(T) = %d \n\n",swaps + comparisons);
        int SsortUP = comparisons+swaps;

        FillRand(N , A);
        // printf("Исходный массив: ");
        // Printer(A, N);
        shakerSort(A, N, &comparisons, &swaps);
        // printf("Отсортированный массив: ");
        // Printer(A, N);
        printf("N : %d",N);
        printf("Теоретическое количество сравнений(%d), перестановок(Ср) (%d)\n", theoretical_comparisons, theoretical_swaps_random);
        printf("Фактическое количество сравнений: %d\n", comparisons);
        printf("Фактическое количество переcтановок: %d\n", swaps);
        printf("Трудоёмкость сортировки(T) = %d \n\n",swaps + comparisons);
        int SsortRAND = comparisons+swaps;



        Tablic_Add(&cur,Tablic_Znach,N,BsortDOWN,BsortRAND,BsortUP,SsortDOWN,SsortRAND,SsortUP);

    }
    
    Tablic(Tablic_Znach);
}