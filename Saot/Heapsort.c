#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int buildComparisons = 0; 
int buildSwaps = 0;        
int sortComparisons = 0;  
int sortSwaps = 0;         
int theoty = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;

}

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

void buildMaxHeap(int arr[], int L, int R) {
    int x = arr[L];
    int i = L;

    while (1) {
        int j = 2 * i + 1;
        if (j > R) break;

        

        (buildComparisons++);if (j < R) {
            (buildComparisons++);if(arr[j + 1] > arr[j])
            {
                j = j + 1;
            }
        }

        (buildComparisons++); if (x >= arr[j]) {
            break;
        }

        (buildComparisons++);arr[i] = arr[j];
        i = j;
    }
    (buildComparisons++);arr[i] = x;
}

void heapSortAscending(int arr[], int n) {
    
    for (int L = n / 2 - 1; L >= 0; L--) {
        buildMaxHeap(arr, L, n - 1);
        theoty += 2 * log((n)/(L+1));
        theoty += log((n)/(L+1)) + L+1;
    }

    
    for (int R = n - 1; R > 0; R--) {
        swap(&arr[0], &arr[R]);
        buildMaxHeap(arr, 0, R - 1);
        theoty += 2 * log((R+1)/1);
        theoty += log((R+1)/1) + 1;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* FillRand(int size, int *massive) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        massive[i] = rand() % 1000000;
    }
    return massive;
}

int main() {
    srand(time(NULL));
    int compRand,compFill,compDie,swapRand,swapDie,swapFill;
    for(int n = 100;n <= 500;n +=100){

    }
    for(int n = 100;n <= 500;n +=100){
        int comparasions_theory = (2*n * (log(n)/log(2))) + n + 2;
        int swaps_theory = (n * (log(n)/log(2))) + (6.5 * n )- 4;

        int *arr = (int*)malloc(sizeof(int) * n);

            FillRand(n, arr);  
            buildComparisons = 0; 
            buildSwaps = 0;        
            sortComparisons = 0;  
            sortSwaps = 0; 
            heapSortAscending(arr, n);
            compRand = sortComparisons + buildComparisons;
            swapRand = sortSwaps + buildSwaps;
            printf("\ntheory = %d\n",theoty);
            theoty = 0;
            

            FillDie(0,n, arr);  
            buildComparisons = 0; 
            buildSwaps = 0;        
            sortComparisons = 0;  
            sortSwaps = 0; 
            heapSortAscending(arr, n);
            compDie = sortComparisons + buildComparisons;
            swapDie = sortSwaps + buildSwaps;
            printf("\ntheory = %d\n",theoty);
            theoty = 0;

            Filllne(n,n, arr);  
            buildComparisons = 0; 
            buildSwaps = 0;        
            sortComparisons = 0;  
            sortSwaps = 0; 
            heapSortAscending(arr, n);
            compFill = sortComparisons + buildComparisons;
            swapFill = sortSwaps + buildSwaps;
            printf("\ntheory = %d\n",theoty);
            theoty = 0;
            printf("%-10d%-10d%-10d%-10d\n",n,swapDie+compDie,compRand+swapRand,compFill+swapFill);
            


    
    free(arr);
    
}

}