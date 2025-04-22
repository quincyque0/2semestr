#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUANTITY 10
#define START 10

typedef struct tData { 
    int data;
    struct tData* next;  
} tData;

typedef struct Queue{ 
    int data;
    struct tData* head;  
    struct tData* tail;  
} Q;



void listIncrease(tData* p,int quantity){
    tData* current = p;
    for(int i = START; i+1 < quantity+START;i++){
        current->next =  (tData*)malloc(sizeof(tData));
        current = current->next;
        current->data = i + 1;
        current->next = NULL;
    }
}
void queueIncrease(Q* p,int quantity){
    Q* current = p;
    for(int i = START; i+1 < quantity+START;i++){
        current->next =  (Q*)malloc(sizeof(Q));
        current = current->next;
        current->data = i + 1;
        current->next = NULL;
    }
    current->tail = &p;
}
void queueDecrease(tData* p,int quantity){

}
void queueRand(tData* p,int quantity){

}
void listDecrease(tData* p,int quantity){
    tData* current = p;
    for(int i = START; i-1 > quantity-START;i--){
        current->next =  (tData*)malloc(sizeof(tData));
        current = current->next;
        current->data = i - 1;
        current->next = NULL;
    }
}
void listRand(tData* p,int quantity){
    tData* current = p;
    current->data = rand() % 10000000;
    for(int i = START; i > quantity-START;i--){
        current->next =  (tData*)malloc(sizeof(tData));
        current = current->next;
        current->data = rand() % 10000000;
        current->next = NULL;
    }
}
void printList(tData* p) {  
    tData* current = p;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
int main(){
    srand(time(NULL));
    tData* p;
    p = (struct tData*)malloc(sizeof(tData));
    p->data = START;
    listDecrease(p,QUANTITY);
    printList(p);
    listIncrease(p,QUANTITY);
    printList(p);
    listRand(p,QUANTITY);
    printList(p);


}