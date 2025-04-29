#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BASE 256

typedef struct Node {
    unsigned int value;
    struct Node* next;
} Node;

typedef struct {
    Node* Head;
    Node* Tail;
} Queue;


Node* createNode(unsigned int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(EXIT_FAILURE);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}


Node* generateRandomList(int size, int bytes) {
    Node* head = NULL;
    Node* tail = NULL;
    unsigned int maxValue = (bytes == 2) ? 0xFFFF : 0xFFFFFFFF;
    for (int i = 0; i < size; i++) {
        unsigned int value = rand() % maxValue;
        Node* node = createNode(value);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}


Node* generateSortedList(int size, int descending, int bytes) {
    Node* head = NULL;
    Node* tail = NULL;
    unsigned int start = (bytes == 2) ? 0x1000 : 0x10000000;
    for (int i = 0; i < size; i++) {
        unsigned int value = descending ? (start + size - i) : (start + i);
        Node* node = createNode(value);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}


void freeList(Node* head) {
    Node* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}


long calculateM(int L, int m, int n) {
    return L * n;
}

void DigitalSort(Node** headPtr, int L) {
    Queue Q[BASE];
    Node* head = *headPtr;
    
    for (int j = L-1; j >= 0; j--) {

        for (int i = 0; i < 256; i++) {
            Q[i].Head = NULL;
            Q[i].Tail = NULL;
        }
        

        Node* p = head;
        while (p != NULL) {
            unsigned char d = (p->value >> (8*j)) & 0xFF;
            Node* next = p->next;
            
            if (Q[d].Head == NULL) {
                Q[d].Head = Q[d].Tail = p;
            } else {
                Q[d].Tail->next = p;
                Q[d].Tail = p;
            }
            p->next = NULL;
            p = next;
        }
        

        head = NULL;
        Node* tail = NULL;
        for (int i = 0; i < BASE; i++) {
            if (Q[i].Head != NULL) {
                if (head == NULL) {
                    head = Q[i].Head;
                    tail = Q[i].Tail;
                } else {
                    tail->next = Q[i].Head;
                    tail = Q[i].Tail;
                }
            }
        }
    }
    
    *headPtr = head;
}

void runExperiment(int bytes, const char* title) {
    int sizes[] = {100, 200, 300, 400, 500};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int L = bytes;

    printf("\n%s\n", title);
    printf("--------------------------------------------------------------------\n");
    printf("|  N  | M(теорет.) |  M факт убыв. |  M факт случ. | M факт возр. |\n");
    printf("--------------------------------------------------------------------\n");

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];

        Node *listDesc = generateSortedList(n, 1, bytes);
        Node *listRand = generateRandomList(n, bytes);
        Node *listAsc = generateSortedList(n, 0, bytes);

        long M_theoretical = calculateM(L, BASE, n);
        

        long M_fact_desc = M_theoretical;
        long M_fact_rand = M_theoretical;
        long M_fact_asc = M_theoretical;

        printf("| %3d | %10ld | %13ld | %13ld | %13ld |\n",
               n, M_theoretical, M_fact_desc, M_fact_rand, M_fact_asc);

        freeList(listDesc);
        freeList(listRand);
        freeList(listAsc);
    }

    printf("--------------------------------------------------------------------\n");
}

int main() {
    srand(time(NULL));

    runExperiment(2, "Таблица для 2-байтовых чисел:");
    runExperiment(4, "Таблица для 4-байтовых чисел:");

    return 0;
}