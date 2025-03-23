#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct phone_info {
    char name[50];
    char surname[50];
    char patronymic[50];
    int phonenumber;
};

int compareBySurname(const struct phone_info *a, const struct phone_info *b, int ascending) {
    int cmp = strcmp(a->surname, b->surname);
    return ascending ? cmp : -cmp;
}

int compareByName(const struct phone_info *a, const struct phone_info *b, int ascending) {
    int cmp = strcmp(a->name, b->name);
    return ascending ? cmp : -cmp;
}

int compareByPatronymic(const struct phone_info *a, const struct phone_info *b, int ascending) {
    int cmp = strcmp(a->patronymic, b->patronymic);
    return ascending ? cmp : -cmp;
}

int compareByPhone(const struct phone_info *a, const struct phone_info *b, int ascending) {
    int cmp = a->phonenumber - b->phonenumber;
    return ascending ? cmp : -cmp;
}

void insertSort(struct phone_info A[], int n, int (*compare)(const struct phone_info *, const struct phone_info *, int), int ascending) {
    for (int i = 1; i < n; i++) {
        struct phone_info temp = A[i];
        int j = i - 1;
        while (j >= 0 && compare(&A[j], &temp, ascending) > 0) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = temp;
    }
}

void printDirectory(struct phone_info A[], int n) {
    printf("%-15s %-15s %-15s %-12s\n", "Surname", "Name", "Patronymic", "Phone Number");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-15s %-15s %-15s %-12d\n", A[i].surname, A[i].name, A[i].patronymic, A[i].phonenumber);
    }
}

int binarySearchBySurname(struct phone_info A[], int n, const char *surname, int ascending) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(A[mid].surname, surname);
        if (cmp == 0) {
            return mid;
        }
        if (ascending ? cmp < 0 : cmp > 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}


int binarySearchByName(struct phone_info A[], int n, const char *name, int ascending) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(A[mid].name, name);
        if (cmp == 0) {
            return mid; 
        }
        if (ascending ? cmp < 0 : cmp > 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; 
}


int binarySearchByPatronymic(struct phone_info A[], int n, const char *patronymic, int ascending) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(A[mid].patronymic, patronymic);
        if (cmp == 0) {
            return mid;
        }
        if (ascending ? cmp < 0 : cmp > 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int binarySearchByPhone(struct phone_info A[], int n, int phone, int ascending) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = A[mid].phonenumber - phone;
        if (cmp == 0) {
            return mid;
        }
        if (ascending ? cmp < 0 : cmp > 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    struct phone_info directory[] = {
        {"Ivan", "Ivanov", "Ivanovich", 1234567},
        {"Petr", "Petrov", "Petrovich", 2345678},
        {"Anna", "Sidorova", "Alexeevna", 3456789},
        {"Maria", "Ivanova", "Sergeevna", 4567890},
        {"Sergey", "Smirnov", "Viktorovich", 5678901}
    };
    int n = sizeof(directory) / sizeof(directory[0]);

    printf("Original Directory:\n");
    printDirectory(directory, n);

    int keyChoice, ascending;
    printf("\nSelect sorting key:\n");
    printf("1. Surname\n");
    printf("2. Name\n");
    printf("3. Patronymic\n");
    printf("4. Phone Number\n");
    printf("Enter your choice: ");
    scanf("%d", &keyChoice);

    printf("\nSelect sorting order:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("Enter your choice: ");
    scanf("%d", &ascending);
    ascending = (ascending == 1);

    int (*compare)(const struct phone_info *, const struct phone_info *, int) = NULL;

    switch (keyChoice) {
        case 1:
            compare = compareBySurname;
            break;
        case 2:
            compare = compareByName;
            break;
        case 3:
            compare = compareByPatronymic;
            break;
        case 4:
            compare = compareByPhone;
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }

    insertSort(directory, n, compare, ascending);

    printf("\nSorted Directory:\n");
    printDirectory(directory, n);

    switch (keyChoice) {
        case 1: {
            char searchSurname[50];
            printf("\nEnter surname to search: ");
            scanf("%s", searchSurname);
            int index = binarySearchBySurname(directory, n, searchSurname, ascending);
            if (index != -1) {
                printf("Found:\n");
                printf("%-15s %-15s %-15s %-12d\n", directory[index].surname, directory[index].name, directory[index].patronymic, directory[index].phonenumber);
            } else {
                printf("Not found.\n");
            }
            break;
        }
        case 2: {
            char searchName[50];
            printf("\nEnter name to search: ");
            scanf("%s", searchName);
            int index = binarySearchByName(directory, n, searchName, ascending);
            if (index != -1) {
                printf("Found:\n");
                printf("%-15s %-15s %-15s %-12d\n", directory[index].surname, directory[index].name, directory[index].patronymic, directory[index].phonenumber);
            } else {
                printf("Not found.\n");
            }
            break;
        }
        case 3: {
            char searchPatronymic[50];
            printf("\nEnter patronymic to search: ");
            scanf("%s", searchPatronymic);
            int index = binarySearchByPatronymic(directory, n, searchPatronymic, ascending);
            if (index != -1) {
                printf("Found:\n");
                printf("%-15s %-15s %-15s %-12d\n", directory[index].surname, directory[index].name, directory[index].patronymic, directory[index].phonenumber);
            } else {
                printf("Not found.\n");
            }
            break;
        }
        case 4: {
            int searchPhone;
            printf("\nEnter phone number to search: ");
            scanf("%d", &searchPhone);
            int index = binarySearchByPhone(directory, n, searchPhone, ascending);
            if (index != -1) {
                printf("Found:\n");
                printf("%-15s %-15s %-15s %-12d\n", directory[index].surname, directory[index].name, directory[index].patronymic, directory[index].phonenumber);
            } else {
                printf("Not found.\n");
            }
            break;
        }
        default:
            printf("Invalid choice!\n");
            return 1;
    }

    return 0;
}