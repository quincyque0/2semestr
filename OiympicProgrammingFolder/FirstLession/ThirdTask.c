#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
 
 int main(){
    char A[100];char B[100];
    scanf("%s", A);
    scanf("%s", B);
    int s1 =0 ,s2 = 0;
    for(int i = 0; i < 100; i++){
        s1 += tolower(A[i]);
        s2 += tolower(B[i]);
    }
    if(s1 > s2){
        printf("-1");
    }
    else if(s1 < s2){
        printf("1");
    }
    else printf("0");
 }