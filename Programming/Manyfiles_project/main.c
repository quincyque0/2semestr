#include "header.h"
int main(){

    FILE *file;
    int file_size;
    
    file = fopen("FourLab.txt", "r");
    
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    
    char *buffer = (char*)malloc(file_size*sizeof(char));
    if (buffer == NULL) {
        perror("Ошибка выделения памяти для buffer");
        fclose(file);
        return 1;
    }
    
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    
    fclose(file);
    
    reverseLongestWord(buffer);
    
    
    free(buffer);
    
    
    
    
    }