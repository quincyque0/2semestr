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
void Tablic_Add7(int *cur, int *tablic, int A,int B,int C,int D,int E,int F,int G){
    tablic[*cur] = A;
    tablic[*cur+1] = B;
    tablic[*cur+2] = C;
    tablic[*cur+3] = D;
    tablic[*cur+4] = E;
    tablic[*cur+5] = F;
    tablic[*cur+6] = G;
    *cur += 7;
}
void Tablic_Add5(int *cur, int *tablic, int A,int B,int C,int D,int E){
    tablic[*cur] = A;
    tablic[*cur+1] = B;
    tablic[*cur+2] = C;
    tablic[*cur+3] = D;
    tablic[*cur+4] = E;
    *cur += 5;
}
void Tablic_Add4(int *cur, int *tablic, int A,int B,int C,int D){
    tablic[*cur] = A;
    tablic[*cur+1] = B;
    tablic[*cur+2] = C;
    tablic[*cur+3] = D;
    *cur += 4;
}
char* stroker(int* numbers,int size){
    
    char str[100] = "";  
    char temp[20];                 

    for (int i = 0; i < size ; i++) {
        snprintf(temp, sizeof(temp), "%d", numbers[i]);
        strcat(str, temp);

        if (i < size - 1) {
            strcat(str, " ");
        }
    }

    printf("Result: %s\n", str);  // Result: 354 43 45

    return 0;
}
int binaryFounder(int *arr, int size , int *comporsions, int *moves, int x){
    comporsions = 0;
    moves = 0;
    int m;

    int L = 0,R = size,Flag = 0;
    while(L < R){
        m = ((L + R) / 2);
        if (arr[m] == x)
        {
            return m;
        }
        if(arr[m < x])
        {
            L = m + 1;
        }
        else R = m - 1;
        
    }
}

int main(){
    int N = 100;
    srand(time(NULL));
    int *A = (int*)malloc(sizeof(int) * 500);
    int *Tablic_Znach = (int*)malloc(sizeof(int) * 16);
    int *Tablic_Znach2 = (int*)malloc(sizeof(int) * 25);
    int comparisons, swaps ,cur = 0,cur2 = 0;
    char *stroke[30];
    Filllne(0,A,N);

}