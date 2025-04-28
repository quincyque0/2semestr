#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>


typedef struct ThreadData{
    char *massage;
    struct ThreadData* next;
} ThreadData;

typedef struct {
    ThreadData *head;
    ThreadData *tail;
} Queue;

typedef struct {
    Queue *q;
    char *massage;
} Node;



void* msgSend(void *argg){
    Node *arg = (Node*)argg;
    ThreadData* new_node = (ThreadData*)malloc(sizeof(ThreadData));
    if (!new_node) {
        printf("утекла все н****\n");
        return NULL;
    }
    new_node->next= NULL;
    new_node->massage = arg->massage;
    
    
    if (arg->q->tail == NULL) {
        arg->q->head = arg->q->tail = new_node;
        return NULL;
    }
    
    arg->q->tail->next = new_node;
    arg->q->tail = new_node;
    return NULL;
}

void* msgRecv(void *qq){
    Queue *q = (Queue*)qq;
    int bufsize = 128;
    if (!q || bufsize <= 0) return NULL;
    if (q->head == NULL) {
        printf("очередь пустая\n");
        return NULL;
    }
    
    char massage[bufsize + 1];
    massage[bufsize] = '\0';

    strncpy(massage,q->head->massage,bufsize);
    massage[bufsize] = '\0'; 

    ThreadData* curr = q->head;   
    q->head = q->head->next;
    free(curr->next);
    free(curr);

    printf("%s\n",massage);
    if(strlen(massage) > bufsize){
        printf("%s\n", "Сообщение обрезано");
    }
    return NULL;
}
    
int main(){

    Queue queue = {NULL, NULL};
   
    char* msg = "hello everybody"; 
    Node zaza = {&queue,msg};
    msgSend(&zaza);
    msgRecv(&queue);

    pthread_t sender;
    pthread_t taker;
    pthread_create(&sender, NULL, msgSend, &zaza);
    pthread_create(&taker, NULL, msgRecv, &queue);


    pthread_join(sender, NULL);
    pthread_join(taker, NULL);
}
