#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 
int main(){
    char *str ="12345689";
    str[0] = '0';
    printf("%s",str);
}