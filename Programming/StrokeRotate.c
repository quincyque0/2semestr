#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 
int main(){
FILE *file;

file = fopen("/Users/a1/Desktop/GitHub/2semestr/Programming/FourLab.txt", "r");

if (file == NULL) {
    perror("Error opening file");
    exit(1);
}

}