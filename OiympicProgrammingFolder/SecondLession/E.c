#include<stdio.h>


int main(){
    char string[201];
    fgets(string, 201, stdin);

    for(int i =0; string[i] != '\n'; i++)
    if(string[i] == '.'){
        printf("%d",0);
    }
    else if(string[i] == '-' && string[i+1]== '.'){
        printf("%d",2);
        i++;
    }
    else if(string[i] == '-' && string[i+1]== '-'){
        printf("%d",1);
        i++;
    }

    
    

}