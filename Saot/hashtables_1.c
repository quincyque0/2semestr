#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Node {
    int key;        
    struct Node* next;
} Node;

int insert(Node** table, int tableSize, int key, int* uniqueKeys) {
    // Проверяем, был ли уже такой ключ
    if (uniqueKeys[key]) {
        return 0; // Уже есть, не добавляем
    }
    
    uniqueKeys[key] = 1; // Помечаем ключ как использованный
    
    int index = key % tableSize;
    Node* head = table[index];

    int collision = (head != NULL);

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(EXIT_FAILURE);
    newNode->key = key;
    newNode->next = head;
    table[index] = newNode;

    return collision;
}

void searchInHash(Node** table, int tableSize, int key) {
    int index = key % tableSize;
    Node* current = table[index];
    int position = 0;
    int found = 0;

    while (current != NULL) {
        if (current->key == key) {
            printf("Элемент '%c' (код %d) найден в списке %d, позиция %d\n", 
                   (char)key, key, index, position);
            found = 1;
            break;
        }
        current = current->next;
        position++;
    }

    if (!found) {
        printf("Элемент '%c' (код %d) не найден в таблице\n", (char)key, key);
    }
}

void freeTable(Node** table, int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        Node* current = table[i];
        while (current) {
            Node* tmp = current;
            current = current->next;
            free(tmp);
        }
    }
    free(table);
}

void generateNotRandomText(char* buffer, size_t size) {
    const char charset[] = "Cambridge English Qua#+lifications are in-depth exams that make learning English enjoyable, effective and rewarding. Our unique approach encourages continuous progression with a clear path to improve language skills. We have qualifications for schools, general and higher education, and business.`";
    for (size_t i = 0; i < size - 1 && i < strlen(charset); i++) {
        buffer[i] = charset[i];
    }
    buffer[size - 1] = '\0';
}

int main() {
    srand(time(NULL));

    const char STATABLE[] = "Cambridge English Qu+a№lifications are in-depth exams that make learning English enjoyable, effective and rewarding. Our unique approach encourages continuous progression with a clear path to improve language skills. We have qualifications for schools, general and higher education, and business.`";
    int primes[] = {11, 23, 31, 43, 53, 61, 67, 71, 79, 101};
    int primesCount = sizeof(primes) / sizeof(primes[0]);

    const size_t textSize = 1024;
    char* text = (char*)malloc(textSize + 1);

    generateNotRandomText(text, textSize + 1);

    printf("\nХеширование текста методом прямого связывания (только уникальные символы)\n");
    printf("+---------------------------------------+\n");
    printf("|   Размер    | Колличество| Количество |\n");
    printf("| хеш-таблицы |  символов  |  коллизий  |\n");
    printf("+---------------------------------------+\n");

    for (int p = 0; p < primesCount; p++) {
        int tableSize = primes[p];

        Node** table = (Node**)calloc(tableSize, sizeof(Node*));
        if (!table) {
            printf("Ошибка выделения памяти для таблицы.\n");
            free(text);
            return 1;
        }

        int collisionCount = 0;
        int uniqueKeys[256] = {0}; 

        for (size_t i = 0; i < textSize && text[i] != '\0'; i++) {
            collisionCount += insert(table, tableSize, (int)text[i], uniqueKeys);
        }

        int uniqueCount = 0;
        for (int i = 0; i < 256; i++) {
            if (uniqueKeys[i]) uniqueCount++;
        }

        printf("| %10d | %10d | %11d |\n", tableSize, uniqueCount, collisionCount);

        freeTable(table, tableSize);
    }

    printf("+---------------------------------------+\n");

    printf("\nДополнительный поиск:\n");
    printf("Введите символ для поиска: ");
    char searchChar;
    scanf(" %c", &searchChar);
    

    int demoTableSize = 17;
    Node** demoTable = (Node**)calloc(demoTableSize, sizeof(Node*));
    int uniqueKeys[256] = {0};
    for (size_t i = 0; i < textSize && text[i] != '\0'; i++) {
        insert(demoTable, demoTableSize, (int)text[i], uniqueKeys);
    }
    
    searchInHash(demoTable, demoTableSize, (int)searchChar);
    freeTable(demoTable, demoTableSize);

    free(text);
    return 0;
}