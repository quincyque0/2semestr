#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main() {
    char filename[25];
    char text[1000];
    FILE *file1;

    printf("Enter filename: ");
    scanf("%s", filename);

    printf("Enter text: ");
    scanf(" %[^\n]", text);

    file1 = fopen(filename, "w");
    fprintf(file1, "%s\n", text); 

    fclose(file1);

    file1 = fopen(filename, "r");

    printf("\nContents of the file:\n");
    char text[1000];
    while (fgets(text, sizeof(text), file1) != NULL) {
        printf("%s", text);
    }

    fclose(file1);

    return 0;
}