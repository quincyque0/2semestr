#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    int comparisons;
    int movements;
} Stats;
typedef struct {
    Node* head;
    Node* tail;
} Queue;


Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node** head, Node** tail, Node* node) {
    if (!node) return;
    if (!*head) {
        *head = *tail = node;
    } else {
        (*tail)->next = node;
        *tail = node;
    }
    node->next = NULL;
}

void print_list(Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void split_list(Node* S, Node** a, Node** b, int* n) {
    if (!S) {
        *a = *b = NULL;
        *n = 0;
        return;
    }

    *a = S;
    *b = S->next;
    *n = 1;
    
    Node* k = *a;
    Node* p = *b;
    
    while (p) {
        (*n)++;
        Node* temp = p->next;
        k->next = temp;
        k = p;
        p = temp;
    }
}

void merge_series(Node* a, int q, Node* b, int r, Node** result, Stats* stats) {
    Node* head = NULL;
    Node* tail = NULL;
    
    while (q != 0 && r != 0 && a && b) {
        stats->comparisons++;
        if (a->data <= b->data) {
            Node* next = a->next;
            append_node(&head, &tail, a);
            a = next;
            q--;
            stats->movements++;
        } else {
            Node* next = b->next;
            append_node(&head, &tail, b);
            b = next;
            r--;
            stats->movements++;
        }
    }
    
    while (q > 0 && a) {
        Node* next = a->next;
        append_node(&head, &tail, a);
        a = next;
        q--;
        stats->movements++;
    }
    
    while (r > 0 && b) {
        Node* next = b->next;
        append_node(&head, &tail, b);
        b = next;
        r--;
        stats->movements++;
    }
    
    *result = head;
}

void merge_sort(Node** S, Stats* stats) {
    if (!*S || !(*S)->next) return;

    Node *a = NULL, *b = NULL;
    int n = 0;
    split_list(*S, &a, &b, &n);
    

    *S = NULL;
    
    merge_sort(&a, stats);
    merge_sort(&b, stats);
    
    Node* merged = NULL;
    merge_series(a, n/2 + n%2, b, n/2, &merged, stats);
        
    *S = merged;
}

Node* create_list_from_array(int* arr, int n) {
    if (!arr || n <= 0) return NULL;

    Node* head = NULL;
    Node* tail = NULL;
    
    for (int i = 0; i < n; i++) {
        Node* new_node = create_node(arr[i]);
        if (!new_node) {
            free_list(head);
            return NULL;
        }
        append_node(&head, &tail, new_node);
    }
    return head;
}

void print_results_table() {
    printf("\nТрудоемкость сортировки слиянием\n");
    printf("+------+---------------+-------+-------+-------+\n");
    printf("|  N   | M+C теоретич. | Убыв  | Возр  | Случ  |\n");
    printf("+------+---------------+-------+-------+-------+\n");
    
    int sizes[] = {100, 200, 300, 400, 500};
    
    for (int i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        int n = sizes[i];
        int* dec = (int*)malloc(n * sizeof(int));
        int* inc = (int*)malloc(n * sizeof(int));
        int* rand_arr = (int*)malloc(n * sizeof(int));
        
        for (int j = 0; j < n; j++) {
            dec[j] = n - j;
            inc[j] = j + 1;
            rand_arr[j] = j + 1;
        }
        
        srand(time(NULL));
        for (int j = n - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            int temp = rand_arr[j];
            rand_arr[j] = rand_arr[k];
            rand_arr[k] = temp;
        }
        
        Node* dec_list = create_list_from_array(dec, n);
        Node* rand_list = create_list_from_array(rand_arr, n);
        Node* inc_list = create_list_from_array(inc, n);
        
        free(dec); free(inc); free(rand_arr);
        
        Stats stats_inc = {0, 0};
        Node* inc_copy = create_list_from_array(NULL, 0);
        Node* inc_tail = NULL;
        Node* temp = inc_list;
        while (temp) {
            Node* new_node = create_node(temp->data);
            append_node(&inc_copy, &inc_tail, new_node);
            temp = temp->next;
        }
        merge_sort(&inc_copy, &stats_inc);

        Stats stats_dec = {0, 0};
        Node* dec_copy = create_list_from_array(NULL, 0);
        Node* dec_tail = NULL;
        temp = dec_list;
        while (temp) {
            Node* new_node = create_node(temp->data);
            append_node(&dec_copy, &dec_tail, new_node);
            temp = temp->next;
        }
        merge_sort(&dec_copy, &stats_dec);
        
        Stats stats_rand = {0, 0};
        Node* rand_copy = create_list_from_array(NULL, 0);
        Node* rand_tail = NULL;
        temp = rand_list;
        while (temp) {
            Node* new_node = create_node(temp->data);
            append_node(&rand_copy, &rand_tail, new_node);
            temp = temp->next;
        }
        merge_sort(&rand_copy, &stats_rand);
        
        printf("| %-4d | %-13d | %-5d | %-5d | %-5d |\n", 
               n, (int)(2*n * log2(n)), 
               stats_dec.comparisons + stats_dec.movements,
               stats_inc.comparisons + stats_rand.movements,
               stats_rand.comparisons + stats_rand.movements);
        
        free_list(dec_list); free_list(rand_list);
        free_list(dec_copy); free_list(rand_copy);
    }
    printf("+------+---------------+-------+-------+-------+\n");
}

int main() {
   
    printf("\n=== Таблица результатов ===\n");
    print_results_table();

    return 0;
}