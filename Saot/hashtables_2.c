#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EMPTY -1
#define DELETED -2

typedef struct {
    int size;
    char* keys;
    int* codes;
    int collisions;
} HashTable;


HashTable* initHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->keys = (char*)malloc(size * sizeof(char));
    ht->codes = (int*)malloc(size * sizeof(int));
    ht->collisions = 0;
    
    for (int i = 0; i < size; i++) {
        ht->keys[i] = EMPTY;
        ht->codes[i] = EMPTY;
    }
    
    return ht;
}


void freeHashTable(HashTable* ht) {
    free(ht->keys);
    free(ht->codes);
    free(ht);
}


int hash(int key, int size) {
    return key % size;
}


int linearProbe(HashTable* ht, int key, int i) {
    return (hash(key, ht->size) + i) % ht->size;
}


int quadraticProbe(HashTable* ht, int key, int i) {
    return (hash(key, ht->size) + i*i) % ht->size;
}


int insert(HashTable* ht, char key, int (*probe)(HashTable*, int, int)) {
    int code = (int)key;
    
    for (int i = 0; i < ht->size; i++) {
        int index = probe(ht, code, i);
        
        if (ht->keys[index] == EMPTY || ht->keys[index] == DELETED) {
            ht->keys[index] = key;
            ht->codes[index] = code;
            if (i > 0) ht->collisions++;
            return index;
        }
        else if (ht->keys[index] == key) {
            return -1; 
        }
    }
    
    return -1; 
}


int search(HashTable* ht, char key, int (*probe)(HashTable*, int, int)) {
    int code = (int)key;
    
    for (int i = 0; i < ht->size; i++) {
        int index = probe(ht, code, i);
        
        if (ht->keys[index] == EMPTY) {
            return -1; 
        }
        else if (ht->keys[index] == key) {
            return index;
        }
    }
    
    return -1; 
}


void printHashTable(HashTable* ht) {
    printf("Номер ячейки: ");
    for (int i = 0; i < ht->size; i++) {
        printf("%3d ", i);
    }
    printf("\nСимвол:      ");
    
    for (int i = 0; i < ht->size; i++) {
        if (ht->keys[i] == EMPTY) {
            printf("   -");
        }
        else if (ht->keys[i] == DELETED) {
            printf("  DEL");
        }
        else {
            printf("%4c", ht->keys[i]);
        }
    }
    printf("\nКод:         ");
    
    for (int i = 0; i < ht->size; i++) {
        if (ht->codes[i] == EMPTY) {
            printf("   -");
        }
        else if (ht->codes[i] == DELETED) {
            printf("  DEL");
        }
        else {
            printf("%4d", ht->codes[i]);
        }
    }
    printf("\n");
}


void generateUniqueText(char* buffer, int size) {
    const char charset[] = "Cambridge English Qu+a№lifications are in-depth exams that make learning English enjoyable, effective and rewarding. Our unique approach encourages continuous progression with a clear path to improve language skills. We have qualifications for schools, general and higher education, and business.`";;
    int used[256] = {0};
    int count = 0;
    
    for (size_t i = 0; i < strlen(charset) && count < size; i++) {
        char c = charset[i];
        if (!used[(int)c] && isprint(c)) {
            buffer[count++] = c;
            used[(int)c] = 1;
        }
    }
    buffer[count] = '\0';
}

int main() {
    int primes[] = {11, 23, 31, 43, 53, 61, 67, 71, 79, 101};
    int primesCount = sizeof(primes) / sizeof(primes[0]);
    const int textSize = 50;
    char text[textSize + 1];
    
    generateUniqueText(text, textSize);
    
    for (int p = 0; p < primesCount; p++) {
        int size = primes[p];
        
        
        HashTable* htLinear = initHashTable(size);
        HashTable* htQuad = initHashTable(size);
        
        
        for (int i = 0; i < strlen(text); i++) {
            insert(htLinear, text[i], linearProbe);
            insert(htQuad, text[i], quadraticProbe);
        }
        if (size == 11) {
            printf("Исходный текст (%d уникальных символов):\n%s\n\n", (int)strlen(text), text);

            
           
            printf("\nХеш-таблица (линейные пробы, размер %d):\n", size);
            printHashTable(htLinear);
            
            printf("\nХеш-таблица (квадратичные пробы, размер %d):\n", size);
            printHashTable(htQuad);
            printf("\n");
            printf("+-------------------------------------------------------------+\n");
            printf("| Размер | Символов | Коллизии (линейные) | Коллизии (квадрат) |\n");
            printf("+-------------------------------------------------------------+\n");
        }
        printf("| %6d | %8d | %18d | %17d |\n", 
               size, (int)strlen(text), htLinear->collisions, htQuad->collisions);
        
        
        
    }
     printf("+-------------------------------------------------------------+\n");
    



    int demoSize = 17;
    HashTable* demoLinear = initHashTable(demoSize);
    HashTable* demoQuad = initHashTable(demoSize);
    
    for (int i = 0; i < strlen(text); i++) {
        insert(demoLinear, text[i], linearProbe);
        insert(demoQuad, text[i], quadraticProbe);
    }
    
    printf("\nДемонстрация поиска (размер таблицы %d):\n", demoSize);
    printf("Введите символ для поиска: ");
    char searchKey;
    scanf(" %c", &searchKey);
    
    int posLinear = search(demoLinear, searchKey, linearProbe);
    int posQuad = search(demoQuad, searchKey, quadraticProbe);
    
    if (posLinear != -1) {
        printf("Линейные пробы: символ '%c' найден в позиции %d\n", searchKey, posLinear);
    } else {
        printf("Линейные пробы: символ '%c' не найден\n", searchKey);
    }
    
    if (posQuad != -1) {
        printf("Квадратичные пробы: символ '%c' найден в позиции %d\n", searchKey, posQuad);
    } else {
        printf("Квадратичные пробы: символ '%c' не найден\n", searchKey);
    }
    
    freeHashTable(demoLinear);
    freeHashTable(demoQuad);
    
    return 0;
}