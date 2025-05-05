#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Student{
    char surname[30];
    char group[30];
    int study[3];
};

void createFile(const char* filename, int N) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Не удалось создать файл.\n");
        return;
    }

    struct Student students[3] = {
        {"Python", "IKS-433", {75, 74, 85}},
        {"Java", "IKS-432", {35, 94, 53}},
        {"Svo", "IKS-431", {100, 53, 52}}
    };

    fwrite(students, sizeof(struct Student), N, file);
    fclose(file);
    printf("Файл успешно создан с %d записями.\n", N);
}
void search(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    int choice;
    printf("\nПо какому полю выполнить поиск?\n1 - Фамилия и инициалы\n2 - Номер группы\n3 - Оценка по предмету \n4 - Оценка по предмету 2\n5 - Оценка по предмету 3\n");
    scanf("%d", &choice);   
    // choice = 4;

    char searchStr[50];
    int searchGrade;
    struct Student s;
    int found = 0;

    switch (choice) {
        case 1:
            printf("Введите фамилию и инициалы: ");
            getchar();
            fgets(searchStr, sizeof(searchStr), stdin);
            searchStr[strcspn(searchStr, "\n")] = '\0';
            break;
        case 2:
            printf("Введите номер группы: ");
            scanf("%s", searchStr);
            break;
        case 3:
        case 4:
        case 5:
            printf("Введите оценку для поиска: ");
            scanf("%d", &searchGrade);
            // searchGrade = 4;
            break;
        default:
            printf("Неверный выбор.\n");
            fclose(file);
            return;
    }

    while (fread(&s, sizeof(struct Student), 1,file) == 1) {
            int match = 0;
            switch (choice) {
                case 1:
                    if (strcmp(s.surname, searchStr) == 0) match = 1;
                    break;
                case 2:
                    if (strcmp(s.group, searchStr) == 0) match = 1;
                    break;
                case 3:
                    if (s.study[0] == searchGrade) match = 1;
                    break;
                case 4:
                    if (s.study[1] == searchGrade) match = 1;
                    break;
                case 5:
                    if (s.study[2] == searchGrade) match = 1;
                    break;
            }
            if (match == 1) {
                printf("%-20s %-20s %-20d %-20d %-20d\n", s.surname, s.group, s.study[0], s.study[1], s.study[2]);
                found = 1;
            
        }
    
    

}

fclose(file);
}

int main(){
    char* filename = "Wedomost.dat";
    int N = 3;
    createFile(filename, N);
    search(filename);
}