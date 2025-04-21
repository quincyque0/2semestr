#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void* plus(){
    for(int i = 0;i <= 5;i++){
        printf("i = %d\n",i);
    }
    return NULL;
}
int main(){
    pthread_t tid;
    pthread_create(&tid, NULL, plus, NULL);
    for(int i = 0;i <= 5;i++){
        printf("i = %d\n",i);
    }
    sleep(3);
}   