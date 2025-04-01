#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct phone_book {
    char name[50];
    char surname[50];
    char patronymic[50];
    int phonenumber;
};


int LessByName(struct phone_book A, struct phone_book B) {
    return strcmp(A.name, B.name) < 0;
}

int LessBySurname(struct phone_book A, struct phone_book B) {
    return strcmp(A.surname, B.surname) < 0;
}


int* initializeIndexArray(int begin, int size, int *massive) {
    for (int i = 0; i < size; i++) {
        massive[i] = begin + i;
    }
    return massive;
}

void indexprint(struct phone_book arr[], int index[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s %s %s %d\n", arr[index[i]].name, arr[index[i]].surname,
               arr[index[i]].patronymic, arr[index[i]].phonenumber);
    }
}

void Selection_sort(struct phone_book arr[], int sizestruct, int index[], int (*Less)(struct phone_book, struct phone_book)) {
    int i, j, min_idx;
    int tmp;

    for (i = 0; i < sizestruct - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < sizestruct; j++)
            if (Less(arr[index[j]], arr[index[min_idx]]))
                min_idx = j;

        tmp = index[i];
        index[i] = index[min_idx];
        index[min_idx] = tmp;
    }
}



int binarySearchName(struct phone_book arr[], int index[], int size, const char *key) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = (size / 2);
        int cmp = strcmp(arr[index[mid]].name, key);

        if (cmp == 0)
            return index[mid]; 
        else if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}


int binarySearchSurname(struct phone_book arr[], int index[], int size, const char *key) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(arr[index[mid]].surname, key);

        if (cmp == 0)
            return index[mid];
        else if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}


int main() {
    struct phone_book directory[] = {
        {"Swifter", "Phperov", "Cssovich", 9136655},
        {"VanGO", "Pascalev", "Asemblerovich", 7770099},
        {"Javio", "Delphino", "Binarycodovich", 1234321},
        {"Cplus", "Phperov", "Htmlovich", 8803306},
        {"Swifter", "Typescriptov", "Asemblerovich", 8803306},
        {"Alice", "Smith", "Unknown", 5551212},
    };

    int size = sizeof(directory) / sizeof(directory[0]);

    int *index_name = malloc(size * sizeof(int));
    if (index_name == NULL) {
        fprintf(stderr, "Ошибка выделения памяти!\n");
        return 1;
    }
    int *index_surname = malloc(size * sizeof(int));
    if (index_surname == NULL) {
        fprintf(stderr, "Ошибка выделения памяти!\n");
        free(index_name);
        return 1;
    }

    initializeIndexArray(0, size, index_name);
    initializeIndexArray(0, size, index_surname);


   
    Selection_sort(directory, size, index_name, LessByName);

    printf("Справочник, отсортированный по имени:\n");
    indexprint(directory, index_name, size);
    printf("\n");

    
    Selection_sort(directory, size, index_surname, LessBySurname);

    printf("Справочник, отсортированный по фамилии:\n");
    indexprint(directory, index_surname, size);
    printf("\n");

    
    char searchName[50];
    printf("Введите имя для поиска: ");
    scanf("%49s", searchName);

    int foundIndexName = binarySearchName(directory, index_name, size, searchName);
    if (foundIndexName != -1) {
        printf("Найдено по имени: %s %s %s %d\n", directory[foundIndexName].name,
               directory[foundIndexName].surname, directory[foundIndexName].patronymic,
               directory[foundIndexName].phonenumber);
    } else {
        printf("Имя '%s' не найдено.\n", searchName);
    }
    printf("\n");


    
    char searchSurname[50];
    printf("Введите фамилию для поиска: ");
    scanf("%49s", searchSurname);

    int foundIndexSurname = binarySearchSurname(directory, index_surname, size, searchSurname);
    if (foundIndexSurname != -1) {
        printf("Найдено по фамилии: %s %s %s %d\n", directory[foundIndexSurname].name,
               directory[foundIndexSurname].surname, directory[foundIndexSurname].patronymic,
               directory[foundIndexSurname].phonenumber);
    } else {
        printf("Фамилия '%s' не найдена.\n", searchSurname);
    }

    free(index_name);
    free(index_surname);

    return 0;
}