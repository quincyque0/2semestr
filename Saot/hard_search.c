#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct phone_info {
    char name[50];
    char surname[50];
    char patronymic[50];
    int phonenumber;
};


int compareBySurname(const struct phone_info *a, const struct phone_info *b) {
    return strcmp(a->surname, b->surname);
}

int compareByName(const struct phone_info *a, const struct phone_info *b) {
    return strcmp(a->name, b->name);
}

int compareByPatronymic(const struct phone_info *a, const struct phone_info *b) {
    return strcmp(a->patronymic, b->patronymic);
}

int compareByPhone(const struct phone_info *a, const struct phone_info *b) {
    return a->phonenumber - b->phonenumber;
}

int less(const struct phone_info *a, const struct phone_info *b,
         int (*primary)(const struct phone_info *, const struct phone_info *),
         int (*secondary)(const struct phone_info *, const struct phone_info *),
         int primaryAscending, int secondaryAscending) {

    int primaryComparison = primary(a, b);
    if (primaryComparison != 0) {
        return primaryAscending ? (primaryComparison < 0) : (primaryComparison > 0);
    }


    int secondaryComparison = secondary(a, b);
    return secondaryAscending ? (secondaryComparison < 0) : (secondaryComparison > 0);
}

void insertSort(struct phone_info A[], int n,
                int (*primary)(const struct phone_info *, const struct phone_info *),
                int (*secondary)(const struct phone_info *, const struct phone_info *),
                int primaryAscending, int secondaryAscending) {
    for (int i = 1; i < n; i++) {
        struct phone_info temp = A[i];
        int j = i - 1;
        while (j >= 0) {
            int cmp = less(&A[j], &temp, primary, secondary, primaryAscending, secondaryAscending);
            if (cmp) {
                A[j + 1] = A[j];
                j--;
            } else {
                break;
            }
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

int main() {
    struct phone_info directory[] = {
        {"Ivan", "Ivanov", "Ivanovich", 1234567},
        {" Ivan", "Petrov", "Petrovich", 2345678},
        {"Anna", "Sidorova", "Alexeevna", 3456789},
        {"Maria", "Ivanova", "Sergeevna", 1234567},
        {"Sergey", "Smirnov", "Viktorovich", 5678901}
    };
    int n = sizeof(directory) / sizeof(directory[0]);

    int primaryChoice, secondaryChoice;
    int primaryAscending, secondaryAscending;

    printf("Choose primary sort key:\n");
    printf("1. Surname\n");
    printf("2. Name\n");
    printf("3. Patronymic\n");
    printf("4. Phone Number\n");
    printf("Enter your choice : ");
    scanf("%d", &primaryChoice);

    printf("ascending ? (1 for yes, 0 for no): ");
    scanf("%d", &primaryAscending);

    printf("Choose secondary sort key:\n");
    printf("1. Surname\n");
    printf("2. Name\n");
    printf("3. Patronymic\n");
    printf("4. Phone Number\n");
    printf("Enter your choice: ");
    scanf("%d", &secondaryChoice);

    printf("ascending ? (1 for yes, 0 for no): ");
    scanf("%d", &secondaryAscending);


    int (*primary)(const struct phone_info *, const struct phone_info *) = NULL;
    int (*secondary)(const struct phone_info *, const struct phone_info *) = NULL;

    switch (primaryChoice) {
        case 1: primary = compareBySurname; break;
        case 2: primary = compareByName; break;
        case 3: primary = compareByPatronymic; break;
        case 4: primary = compareByPhone; break;
        default: printf("Invalid primary key choice.\n"); return 1;
    }

    switch (secondaryChoice) {
        case 1: secondary = compareBySurname; break;
        case 2: secondary = compareByName; break;
        case 3: secondary = compareByPatronymic; break;
        case 4: secondary = compareByPhone; break;
        default: printf("Invalid secondary key choice.\n"); return 1;
    }
    if (primaryChoice == secondaryChoice) {
        printf("Primary and secondary keys cannot be the same.\n");
        return 1;
    }

    printf("Before sorting:\n");
    printDirectory(directory, n);

    insertSort(directory, n, primary, secondary, primaryAscending, secondaryAscending);

    printf("\nAfter sorting:\n");
    printDirectory(directory, n);

    return 0;
}