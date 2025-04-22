#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUANTITY 10
#define START 10

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

void push(Node** top, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = *top;
    *top = new_node;
}

int pop(Node** top) {
    if (*top == NULL) {
        printf("Stack underflow!\n");
        exit(1);
    }
    Node* temp = *top;
    int value = temp->data;
    *top = (*top)->next;
    free(temp);
    return value;
}

void stackIncrease(Node** top, int quantity) {
    for (int i = START + quantity - 1; i >= START; i--) {
        push(top, i);
    }
}

void stackDecrease(Node** top, int quantity) {
    for (int i = START; i < START + quantity; i++) {
        push(top, i);
    }
}

void stackRand(Node** top, int quantity) {
    srand(time(NULL));
    for (int i = 0; i < quantity; i++) {
        push(top, rand() % 10000000);
    }
}

void enqueue(Queue* q, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = NULL;
    
    if (q->tail == NULL) {
        q->head = q->tail = new_node;
        return;
    }
    
    q->tail->next = new_node;
    q->tail = new_node;
}

int dequeue(Queue* q) {
    if (q->head == NULL) {
        printf("Queue underflow!\n");
        exit(1);
    }
    Node* temp = q->head;
    int value = temp->data;
    q->head = q->head->next;
    
    if (q->head == NULL) {
        q->tail = NULL;
    }
    
    free(temp);
    return value;
}

void queueIncrease(Queue* q, int quantity) {
    for (int i = START; i < START + quantity; i++) {
        enqueue(q, i);
    }
}

void queueDecrease(Queue* q, int quantity) {
    for (int i = START + quantity - 1; i >= START; i--) {
        enqueue(q, i);
    }
}

void queueRand(Queue* q, int quantity) {
    srand(time(NULL));
    for (int i = 0; i < quantity; i++) {
        enqueue(q, rand() % 10000000);
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int calculateChecksum(Node* head) {
    int sum = 0;
    Node* current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

int countSeries(Node* head) {
    if (head == NULL) return 0;
    int count = 1;
    Node* current = head;
    while (current->next != NULL) {
        if (current->data > current->next->data) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void clearList(Node** head) {
    Node* current = *head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

void printForwardRecursive(Node* node) {
    if (node == NULL) {
        printf("\n");
        return;
    }
    printf("%d ", node->data);
    printForwardRecursive(node->next);
}

void printBackwardRecursive(Node* node) {
    if (node == NULL) {
        return;
    }
    printBackwardRecursive(node->next);
    printf("%d ", node->data);
}

void clearQueue(Queue* q) {
    while (q->head != NULL) {
        dequeue(q);
    }
}

int main() {
    srand(time(NULL));

    printf("STACK OPERATIONS:\n");
    Node* stack = NULL;
    
    printf("Increasing stack: ");
    stackIncrease(&stack, QUANTITY);
    printList(stack);
    printf("Series count: %d\n", countSeries(stack));
    printf("Checksum: %d\n", calculateChecksum(stack));
    clearList(&stack);
    printf("\n");
    
    printf("Decreasing stack: ");
    stackDecrease(&stack, QUANTITY);
    printList(stack);
    printf("Series count: %d\n", countSeries(stack));
    printf("Checksum: %d\n", calculateChecksum(stack));
    clearList(&stack);
    printf("\n");
    
    printf("Random stack: ");
    stackRand(&stack, QUANTITY);
    printList(stack);
    printf("Series count: %d\n", countSeries(stack));
    printf("Checksum: %d\n", calculateChecksum(stack));
    printf("Recursive forward: ");
    printForwardRecursive(stack);
    printf("Recursive backward: ");
    printBackwardRecursive(stack);
    printf("\n\n\n");
    clearList(&stack);

    printf("\nQUEUE OPERATIONS:\n");
    

    Queue queue1 = {NULL, NULL};
    printf("Increasing queue: ");
    queueIncrease(&queue1, QUANTITY);
    printList(queue1.head);
    printf("Series count: %d\n", countSeries(queue1.head));
    printf("Checksum: %d\n", calculateChecksum(queue1.head));
    clearQueue(&queue1);
    printf("\n");
    

    Queue queue2 = {NULL, NULL};
    printf("Decreasing queue: ");
    queueDecrease(&queue2, QUANTITY);
    printList(queue2.head);
    printf("Series count: %d\n", countSeries(queue2.head));
    printf("Checksum: %d\n", calculateChecksum(queue2.head));
    clearQueue(&queue2);
    printf("\n");
    

    Queue queue3 = {NULL, NULL};
    printf("Random queue: ");
    queueRand(&queue3, QUANTITY);
    printList(queue3.head);
    printf("Series count: %d\n", countSeries(queue3.head));
    printf("Checksum: %d\n", calculateChecksum(queue3.head));
    printf("Recursive forward: ");
    printForwardRecursive(queue3.head);
    printf("Recursive backward: ");
    printBackwardRecursive(queue3.head);
    printf("\n");
    clearQueue(&queue3);
    
    return 0;
}