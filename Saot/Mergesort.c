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
} Queue;


typedef struct {
    int comparisons;
    int movements;
} Stats;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
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
    
    while (q != 0 && r!= 0) {
        stats->comparisons++;
        if (a->data <= b->data) {
            append_node(&(c->head), &(c->tail), create_node(a->data));
            a = a->next;
            q -=1;
            stats->movements++;
        } else {
            append_node(&(c->head), &(c->tail), create_node(b->data));
            b = b->next;
            r -=1;
            stats->movements++;
        }
    }
    
    while (q > 0) {
        append_node(&(c->head), &(c->tail), create_node(a->data));
        a = a->next;
        q-=1;
        stats->movements++;
    }
    
    while (r > 0) {
        append_node(&(c->head), &(c->tail), create_node(b->data));
        b = b->next;
        q-=1;
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
            
            int r = (m >= p) ? p : m;
            m -= r;
            
            merge_series(a, q, b, r, &c[i], stats);
            i = 1 - i;
        }
        
        a = c[0].head;
        b = c[1].head;
        p *= 2;
    }
    
    
    c[0].tail->next = NULL;
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
    
    for (int i = 0; i < n; i++) {
        dec[i] = n - i;
        inc[i] = i + 1;
        rand_arr[i] = i + 1;
    }
    
    // Перемешиваем для случайного случая
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

void print_results_table() {
    printf("\nТрудоемкость сортировки с распределением серий\n");
    printf("+----------------------------------------------+\n");
    printf("|  N   | M+C теоретич. | Убыв. | Случ. | Возр. |\n");
    
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        Node *dec, *inc, *rand_case;
        
        generate_test_cases(n, &dec, &inc, &rand_case);
        
        int theoretical = (int)(2 * n * (log(n) / log(2)));
        
        Stats stats_dec = {0, 0};
        Node* dec_copy = create_list_from_array(NULL, 0);
        Node* temp = dec;
        while (temp != NULL) {
            append_node(&dec_copy, &dec_copy, create_node(temp->data));
            temp = temp->next;
        }
        distribution_sort(&dec_copy, &stats_dec);
        
        Stats stats_rand = {0, 0};
        Node* rand_copy = create_list_from_array(NULL, 0);
        temp = rand_case;
        while (temp != NULL) {
            append_node(&rand_copy, &rand_copy, create_node(temp->data));
            temp = temp->next;
        }
        distribution_sort(&rand_copy, &stats_rand);
        
        Stats stats_inc = {0, 0};
        Node* inc_copy = create_list_from_array(NULL, 0);
        temp = inc;
        while (temp != NULL) {
            append_node(&inc_copy, &inc_copy, create_node(temp->data));
            temp = temp->next;
        }
        distribution_sort(&inc_copy, &stats_inc);
        
        printf("+------+---------------+-------+-------+-------+\n");
        printf("| %-4d | %-13d | %-5d | %-5d | %-5d |\n", 
               n, theoretical, 
               stats_dec.comparisons + stats_dec.movements,
               stats_rand.comparisons + stats_rand.movements,
               stats_inc.comparisons + stats_inc.movements);
        
        // Освобождение памяти
        while (dec != NULL) {
            Node* temp = dec;
            dec = dec->next;
            free(temp);
        }
        while (inc != NULL) {
            Node* temp = inc;
            inc = inc->next;
            free(temp);
        }
        while (rand_case != NULL) {
            Node* temp = rand_case;
            rand_case = rand_case->next;
            free(temp);
        }
    }
    printf("+----------------------------------------------+\n");
}

// ===== Основная функция =====
int main() {
    srand(time(NULL));
    
    printf("=== Задание 2: Расщепление списка ===\n");
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    Node* S = create_list_from_array(arr, sizeof(arr)/sizeof(arr[0]));
    
    Node *a, *b;
    int n;
    split_list(S, &a, &b, &n);
    
    printf("Исходный список: ");
    print_list(S);
    printf("Список a: ");
    print_list(a);
    printf("Список b: ");
    print_list(b);
    printf("Количество элементов: %d\n", n);
    
    printf("\n=== Задание 3: Слияние серий ===\n");
    int left_arr[] = {1, 3, 5};
    int right_arr[] = {2, 4, 6};
    Node* left = create_list_from_array(left_arr, 3);
    Node* right = create_list_from_array(right_arr, 3);
    
    Queue c = {NULL, NULL};
    Stats stats = {0, 0};
    merge_series(left, 3, right, 3, &c, &stats);
    
    printf("Левый список: ");
    print_list(left);
    printf("Правый список: ");
    print_list(right);
    printf("Результат слияния: ");
    print_list(c.head);
    printf("Количество сравнений (Cф): %d\n", stats.comparisons);
    printf("Количество перемещений (Mф): %d\n", stats.movements);
    
    printf("\n=== Задание 4: Сортировка с распределением серий ===\n");
    int unsorted_arr[] = {5, 3, 8, 6, 2, 7, 1, 4};
    Node* unsorted = create_list_from_array(unsorted_arr, 8);
    
    printf("Исходный список: ");
    print_list(unsorted);
    
    Stats stats2 = {0, 0};
    distribution_sort(&unsorted, &stats2);
    
    printf("Отсортированный список: ");
    print_list(unsorted);
    printf("Фактические сравнения (Cф): %d\n", stats2.comparisons);
    printf("Фактические перемещения (Mф): %d\n", stats2.movements);
    
    printf("\n=== Задание 5: Таблица трудоемкости ===\n");
    print_results_table();
    
    return 0;
}