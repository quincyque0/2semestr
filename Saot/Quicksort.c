#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int moves = 0;
int comparisons = 0;

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

    
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
    moves++;
  }
  void quickSortRecursive(int *arr, int low, int high) {
    int x = arr[low],i = low,j = high;
    while (i<=j)
    {
        while(arr[i] < x) i = i + 1;comparisons++;
        while(arr[j] > x) j = j - 1;comparisons++;
        if(i <= j){ swap(&arr[i],&arr[j]);i = i + 1; j = j - 1;}
    }
    if (low < j) quickSortRecursive(arr,low,j);
    if (i < high) quickSortRecursive(arr,i,high);
    
}


void quickSort(int arr[], int n) {
    moves = 0;
    comparisons = 0;
    quickSortRecursive(arr, 0, n - 1);
}
int comparisonCount = 0;
int swapCount = 0;
int main() {
    int n = 10;
    int *a = (int*)malloc(sizeof(int)*n);
    FillDie(100,n,a);
    quickSort(a,n);
    srand(time(NULL));
    Printer(a,n);
}