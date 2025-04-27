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
void digitalSort(){
    
}
int main(){

}