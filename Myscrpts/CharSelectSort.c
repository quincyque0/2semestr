#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue; // Queue не совсем очередь.  Это скорее просто структура для хранения головы и хвоста связного списка.

typedef struct {
    int comparisons;
    int movements;
} Stats;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) { // Важно проверять результат malloc
        fprintf(stderr, "Не удалось выделить память для узла!\n");
        exit(1); // Важно выйти из программы, если не удалось выделить память.
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node** head, Node** tail, Node* node) {
    if (*head == NULL) {
        *head = node;
        *tail = node;
    } else {
        (*tail)->next = node;
        *tail = node;
    }
}

void print_list(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}


void split_list(Node* S, Node** a, Node** b, int* n) {
    *a = S;
    *b = S->next;
    *n = 1;

    Node* k = *a;
    Node* p = *b;

    while (p != NULL) {
        (*n)++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
}

// ===== 3. Подпрограмма слияния серий =====
void merge_series(Node* a, int q, Node* b, int r, Queue* c, Stats* stats) {
    int i = 0, j = 0;

    // Добавлена проверка на NULL для a и b в начале цикла
    while (i < q && j < r && a != NULL && b != NULL) {
        stats->comparisons++;
        if (a->data <= b->data) {
            append_node(&(c->head), &(c->tail), create_node(a->data));
            a = a->next;
            i++;
            stats->movements++;
        } else {
            append_node(&(c->head), &(c->tail), create_node(b->data));
            b = b->next;
            j++;
            stats->movements++;
        }
    }

    while (i < q && a != NULL) {
        append_node(&(c->head), &(c->tail), create_node(a->data));
        a = a->next;
        i++;
        stats->movements++;
    }

    while (j < r && b != NULL) {
        append_node(&(c->head), &(c->tail), create_node(b->data));
        b = b->next;
        j++;
        stats->movements++;
    }
}

// ===== 4. Модифицированная подпрограмма сортировки =====
void distribution_sort(Node** S, Stats* stats) {
    Node *a, *b;
    int n;
    split_list(*S, &a, &b, &n);
    Queue c[2];
    int p = 1;

    while (p < n) {
        // Инициализация очередей
        c[0].head = c[0].tail = NULL;
        c[1].head = c[1].tail = NULL;

        int i = 0;
        int m = n;

        while (m > 0) {
            int q = (m >= p) ? p : m;
            m -= q;

            int r = (m >= p) ? p : m; // Ошибка: r должно зависеть от оставшегося m
            m -= r;

            merge_series(a, q, b, r, &c[i], stats);
            i = 1 - i;
        }

        a = c[0].head;
        b = c[1].head;
        p *= 2;
    }

    if (c[0].tail != NULL) {
        c[0].tail->next = NULL;
    }
    *S = c[0].head;
}

// ===== 5. Генерация тестовых данных и таблица =====
Node* create_list_from_array(int* arr, int n) {
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < n; i++) {
        Node* new_node = create_node(arr[i]);
        if (head == NULL) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    return head;
}

void generate_test_cases(int n, Node** decreasing, Node** increasing, Node** random_case) {
    int* dec = (int*)malloc(n * sizeof(int));
    int* inc = (int*)malloc(n * sizeof(int));
    int* rand_arr = (int*)malloc(n * sizeof(int));

    if (dec == NULL || inc == NULL || rand_arr == NULL) { // Проверка на ошибки malloc
        fprintf(stderr, "Не удалось выделить память для тестовых данных!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        dec[i] = n - i;
        inc[i] = i + 1;
        rand_arr[i] = i + 1;
    }

    // Перемешиваем для случайного случая
    srand(time(NULL)); // Инициализация генератора случайных чисел один раз в начале
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = rand_arr[i];
        rand_arr[i] = rand_arr[j];
        rand_arr[j] = temp;
    }

    *decreasing = create_list_from_array(dec, n);
    *increasing = create_list_from_array(inc, n);
    *random_case = create_list_from_array(rand_arr, n);

    free(dec);
    free(inc);
    free(rand_arr);
}

