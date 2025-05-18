#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rand_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;
int ttl = 30;
int running = 1;

typedef struct ThreadData {
    char *message;
    struct ThreadData* next;
    int num;
} ThreadData;

typedef struct {
    ThreadData *head;
    ThreadData *tail;
} Queue;

Queue queue = {NULL, NULL};

void update_graph_file() {
    pthread_mutex_lock(&file_mutex);
    FILE *fp = fopen("graph.dot", "w");
    if (fp == NULL) {
        fprintf(stderr, "Ошибка открытия файла для записи!\n");
        pthread_mutex_unlock(&file_mutex);
        return;
    }
    
    fprintf(fp, "digraph LinkedList {\n");
    fprintf(fp, "node [shape=circle];\n");
    fprintf(fp, "rankdir=UD;\n");

    pthread_mutex_lock(&queue_mutex);
    ThreadData *current = queue.head;
    while (current != NULL) {
        char escaped_msg[256];
        int j = 0;
        for (int i = 0; current->message[i] != '\0' && j < 255; i++) {
            if (current->message[i] == '"' || current->message[i] == '\\') {
                escaped_msg[j++] = '\\';
            }
            escaped_msg[j++] = current->message[i];
        }
        escaped_msg[j] = '\0';
        
        fprintf(fp, "  node%d [label=\"%d: %s\"];\n", current->num, current->num, escaped_msg);
        if (current->next != NULL) {
            fprintf(fp, "  node%d -> node%d;\n", current->num, current->next->num);
        }
        current = current->next;
    }
    pthread_mutex_unlock(&queue_mutex);
    
    fprintf(fp, "}\n");
    fclose(fp);
    pthread_mutex_unlock(&file_mutex);
}

int safe_rand(int max) {
    pthread_mutex_lock(&rand_mutex);
    int result = rand() % max;
    pthread_mutex_unlock(&rand_mutex);
    return result;
}

unsigned int portable_rand_r(unsigned int *seed) {
    unsigned int next = *seed;
    next *= 1103515245;
    next += 12345;
    *seed = next;
    return (unsigned int)(next / 65536) % 32768;
}

char* get_message() {
    const char* first_part[] = {
        "Я иду", "Ты знаешь", "Мы видели", "Он сказал",
        "Она пришла", "Вы слышали", "Они любят", "Я хочу",
        "Мы можем", "Ты помнишь", "Он забыл", "Она нашла",
        "Вы видели", "Я сделал", "Мы знаем", "Ты понимаешь"
    };
    
    const char* second_part[] = {
        "домой", "это место", "вчера вечером", "мне правду",
        "совсем одна", "эту песню", "мороженое", "кофе",
        "завтра утром", "тот день", "свой пароль", "деньги",
        "этот фильм", "свою ошибку", "этого человека", "нас"
    };
    
    char* message = malloc(50);
    snprintf(message, 50, "%s %s", first_part[safe_rand(16)], second_part[safe_rand(16)]);
    
    return message;
}

void* sender_thread(void *arg) {
    unsigned int seed = time(NULL) ^ (unsigned long)pthread_self();;
    
    while(running) {
        int delay = 1 + (portable_rand_r(&seed) % 3);
        if(queue.tail != NULL){
            if(queue.tail->num > 10) delay += 10;}
        sleep(delay);
        
        char* msg = get_message();
        
        ThreadData* new_node = malloc(sizeof(ThreadData));
        if (!new_node) {
            printf("Ошибка выделения памяти\n");
            free(msg);
            continue;
        }
        new_node->next = NULL;
        new_node->message = msg;
        
        pthread_mutex_lock(&queue_mutex);
        
        if (queue.tail == NULL) {
            new_node->num = 1;
            queue.head = queue.tail = new_node;
        } else {
            new_node->num = queue.tail->num + 1;
            queue.tail->next = new_node;
            queue.tail = new_node;
        }
        
        pthread_mutex_unlock(&queue_mutex);
        
        printf("Отправитель %lu добавил: %s (#%d)\n", pthread_self()-1, msg, new_node->num);
        update_graph_file();
    }
    return NULL;
}

void* receiver_thread(void *arg) {
    unsigned int seed = time(NULL) ^ (unsigned long)pthread_self();;
    int bufsize = 128;
    char message[bufsize + 1];
    
    while(running) {
        int delay = 1 + (portable_rand_r(&seed) % 5);
        sleep(delay);
        
        pthread_mutex_lock(&queue_mutex);
        
        if (queue.head == NULL) {
            pthread_mutex_unlock(&queue_mutex);
            continue;
        }
        
        strncpy(message, queue.head->message, bufsize);
        message[bufsize] = '\0';
        
        ThreadData* curr = queue.head;
        queue.head = queue.head->next;
        if (queue.head == NULL) {
            queue.tail = NULL;
        }
        
        pthread_mutex_unlock(&queue_mutex);
        
        printf("Получатель %lu получил: %s\n", pthread_self()-1, message);
        if(strlen(curr->message) > bufsize) {
            printf("Сообщение обрезано\n");
        }
        
        free(curr->message);
        free(curr);
        update_graph_file();
    }
    return NULL;
}

void* code_break(void *arg) {
    sleep(*(int*)arg);
    running = 0;
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t breaker;
    pthread_create(&breaker, NULL, code_break, &ttl);

    pthread_t senders[3], receivers[3];
    
    update_graph_file();
    
    for (int i = 0; i < 3; i++) {
        pthread_create(&senders[i], NULL, sender_thread, NULL);
        pthread_create(&receivers[i], NULL, receiver_thread, NULL);
        sleep(1);
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_join(senders[i], NULL);
        pthread_join(receivers[i], NULL);
    }
    
    pthread_join(breaker, NULL);
    return 0;
}