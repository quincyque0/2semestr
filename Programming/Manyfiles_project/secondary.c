#include "header.h"
void reverseWord(char *start, char *end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}
void reverseLongestWord(char *str) {
    char *longestStart = NULL;
    char *longestEnd = NULL;  
    char *currentStart = NULL;
    int maxLength = 0;         
    int currentLength = 0;     

    for (char *p = str; *p != '\0'; p++) {
        if (isalpha(*p)) {
            if (currentStart == NULL) {
                currentStart = p;
            }
            currentLength++;
        } else { 
            if (currentLength > maxLength) {
                maxLength = currentLength;
                longestStart = currentStart;
                longestEnd = p - 1;
            }
            currentStart = NULL;
            currentLength = 0;
        }
    }

    if (currentLength > maxLength) {
        maxLength = currentLength;
        longestStart = currentStart;
        longestEnd = str + strlen(str) - 1;
    }

    printf("Rotated word: ");
    for (char *p = longestStart; p <= longestEnd; p++) {
        printf("\033[32m%c\033[0m", *p);
    }
    printf("\n\n");

    if (longestStart != NULL && longestEnd != NULL) {
        reverseWord(longestStart, longestEnd);
    }
    printf("Modified string: ");
        for (char *p = str; *p != '\0'; p++) {
            if (p == longestStart) {
                
                printf("\033[32m");
            }
            printf("%c", *p);
            if (p == longestEnd) {
                
                printf("\033[0m");
            }
        }
}