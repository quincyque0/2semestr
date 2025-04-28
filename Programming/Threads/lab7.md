1.	Создать поток

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
        sleep(1);
    }   
![alt text](image.png)

2.	Ожидание потока

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
        pthread_join(tid,NULL);
        for(int i = 0;i <= 5;i++){
            printf("i = %d\n",i);
        }
    }   
    ![alt text](image-1.png)

3-5. 
    #include <stdio.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include <unistd.h>
    #include <string.h>

    typedef struct {
        char **messages;
        int start;
        int count;
    } ThreadData;

    void cleanup(void *arg) {
        printf("Поток %lu завершает работу (был отменен)\n", pthread_self());
    }

    void* plus(void *arg) { 

        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        ThreadData *data = (ThreadData*)arg;
        pthread_cleanup_push(cleanup, NULL);
        
        for(int i = 0; i < data->count; i++) {
            printf("Поток %lu: %s\n", pthread_self(), data->messages[data->start + i]);
            sleep(1);
            pthread_testcancel();
        }
        
        free(data);
        printf("Поток %lu завершил работу (нормально)\n", pthread_self());
        

        pthread_cleanup_pop(0);
        return NULL;
    }

    int main() {
        char* messages[] = {
            "Объявлен международный тендер на прокладку трубопровода по дну океана из Европы в Америку. Проект представляет немецкая компания, показывает графики, схемы, сметы.",
            "- Мы будем работать три года. Начнем с двух сторон. Когда дойдем до середины, гарантируем, что расхождение будет не более десяти метров.",
            "Японская компания, показывает проект:",
            "- Мы будем работать два года. Начнем с двух сторон. Когда дойдем до середины, гарантируем, что расхождение будет не более пяти метров.",
            "Русская компания:",
            "- Мы будем работать полгода. Начнем с двух сторон. Ничего не гарантируем. В крайнем случае, будет две трубы.",
            "Объявлен международный тендер на прокладку трубопровода по дну океана из Европы в Америку. Проект представляет немецкая компания, показывает графики, схемы, сметы.",
            "- ы будем работать три года. Начнем с двух сторон. Когда дойдем до середины, гарантируем, что расхождение будет не более десяти метров.",
            "Японская компания, показывает проект:",
            "- ы будем работать два года. Начнем с двух сторон. Когда дойдем до середины, гарантируем, что расхождение будет не более пяти метров.",
            "Русская компания:",
            "- ы будем работать полгода. Начнем с двух сторон. Ничего не гарантируем. В крайнем случае, будет две трубы.",
            "Объявлен международный тендер на прокладку трубопровода по дну океана из Европы в Америку. Проект представляет немецкая компания, показывает графики, схемы, сметы.",
            "-  будем работать три года. Начнем с двух сторон. Когда дойдем до середины, гарантируем, что расхождение будет не более десяти метров.",
            "Японская компания, показывает проект:",
            "-  будем работать два года. Начнем с двух сторон. Когда дойдем до середины, гарантируем, что расхождение будет не более пяти метров.",
            "Русская компания:",
            "-  будем работать полгода. Начнем с двух сторон. Ничего не гарантируем. В крайнем случае, будет две трубы.",
            NULL
        };


        int total_messages = 0;
        while(messages[total_messages] != NULL) total_messages++;

        pthread_t threads[4];
        int messages_per_thread = total_messages / 4;
        int remainder = total_messages % 4;
        int current_start = 0;

        for(int i = 0; i < 4; i++) {
            ThreadData *data = malloc(sizeof(ThreadData));
            data->messages = messages;
            data->start = current_start;
            
            data->count = messages_per_thread;
            if (i < remainder) data->count++; 
            
            pthread_create(&threads[i], NULL, plus, data);
            
            current_start += data->count;
        }
        sleep(2);
        for(int i = 0; i < 4; i++) {
            pthread_cancel(threads[i]);
        }
        for(int i = 0; i < 4; i++) {
            pthread_join(threads[i], NULL);
        }
        
    }   
    
![alt text](image-2.png)
6.	Реализовать простой Sleepsort
![alt text](image-3.png)
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
void printer(int* arr){
    for(int i = 0 ;i < 50; i++){
        printf("%d ",arr[i]);
        
    }
    printf("\n");
}
void* sorted(void *arg){
    int argi = *(int*)arg;
    sleep(argi);
    printf("%d ",argi);
    return NULL;
}
int main(){
    srand(time(NULL));
    pthread_t threads[50];
    int* a = malloc(sizeof(int)* 50);
    
    for(int i = 0 ; i < 50;i++){
        a[i] = rand() % 60;
    }
    printer(a);
    
    for(int i = 0;i < 50;i++){
        pthread_create(&threads[i],NULL,sorted,&a[i]);
    }
    for(int i = 0; i < 50; i++) {
        pthread_join(threads[i], NULL);
    }
}
7.	Синхронизированный вывод
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int curstr = 0;
int turn = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void cleanup(void *arg) {
    printf("Поток %lu завершает работу (был отменен)\n", pthread_self());
}

void* plus(void *arg) {
    char **messages = (char**)arg;
    
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_cleanup_push(cleanup, NULL);

    while(1) {
        pthread_mutex_lock(&mutex);
        
        while(turn != 1 && messages[curstr] != NULL) {
            pthread_cond_wait(&cond, &mutex);
        }
        
        if(messages[curstr] == NULL) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        
        printf("Дочерний поток: %s\n", messages[curstr++]);
        turn = 0; // Передаем ход главному потоку
        pthread_cond_signal(&cond);
        
        pthread_mutex_unlock(&mutex);
    }

    printf("Поток %lu завершил работу\n", pthread_self());
    pthread_cleanup_pop(0);
    return NULL;
}
```c
int main() {
    char* messages[] = {
        "Объявлен международный тендер на прокладку трубопровода по дну океана из Европы в Америку. Проект представляет немецкая компания, показывает графики, схемы, сметы.",
        "- Мы будем работать три года. Начнем с двух сторон. Когда дойдем до середины, гарантируем, что расхождение будет не более десяти метров.",
        "Японская компания, показывает проект:",
        "- Мы будем работать два года. Начнем с двух сторон. Когда дойдем до середины, гарантируем, что расхождение будет не более пяти метров.",
        "Русская компания:",
        "- Мы будем работать полгода. Начнем с двух сторон. Ничего не гарантируем. В крайнем случае, будет две трубы.",
        NULL
    };

    pthread_t thread;
    pthread_create(&thread, NULL, plus, messages);

    while(1) {
        pthread_mutex_lock(&mutex);
        
        
        while(turn != 0 && messages[curstr] != NULL) {
            pthread_cond_wait(&cond, &mutex);
        }
        
        if(messages[curstr] == NULL) {
            turn = 1;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
            break;
        }
        
        printf("Главный поток: %s\n", messages[curstr++]);
        turn = 1;
        pthread_cond_signal(&cond);
        
        pthread_mutex_unlock(&mutex);
    }

    pthread_join(thread, NULL);
    
    
    return 0;
}
```
![alt text](image-4.png)
8.	Перемножение квадратных матриц NxN
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>

#define MAX_THREADS 64
#define MAX_SIZE 500
#define STEP_SIZE 10
#define THREAD_STEP 2

typedef struct {
    double **A;
    double **B;
    double **C;
    int N;
    int start_row;
    int end_row;
} ThreadData;

void initialize_matrix(double **matrix, int N, int value) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = value;
        }
    }
}

void print_matrix(double **matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.0f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void* multiply_part(void *arg) {
    ThreadData *data = (ThreadData*)arg;
    
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->N; j++) {
            data->C[i][j] = 0;
            for (int k = 0; k < data->N; k++) {
                data->C[i][j] += data->A[i][k] * data->B[k][j];
            }
        }
    }
    
    pthread_exit(NULL);
}

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

void run_test(int N, int num_threads, FILE *results_file) {
    double **A = (double**)malloc(N * sizeof(double*));
    double **B = (double**)malloc(N * sizeof(double*));
    double **C = (double**)malloc(N * sizeof(double*));
    
    for (int i = 0; i < N; i++) {
        A[i] = (double*)malloc(N * sizeof(double));
        B[i] = (double*)malloc(N * sizeof(double));
        C[i] = (double*)malloc(N * sizeof(double));
    }

    initialize_matrix(A, N, 1);
    initialize_matrix(B, N, 1);

    pthread_t *threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
    ThreadData *thread_data = (ThreadData*)malloc(num_threads * sizeof(ThreadData));

    int rows_per_thread = N / num_threads;
    int remaining_rows = N % num_threads;
    
    double start_time = get_time();

    int current_row = 0;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].N = N;
        thread_data[i].start_row = current_row;
        
        int rows = rows_per_thread;
        if (i < remaining_rows) {
            rows++;
        }
        
        thread_data[i].end_row = current_row + rows;
        current_row += rows;
        
        pthread_create(&threads[i], NULL, multiply_part, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    double end_time = get_time();
    double elapsed_time = (end_time - start_time) * 1000;

    fprintf(results_file, "%d,%d,%.2f\n", N, num_threads, elapsed_time);
    printf("N=%d, поток=%d, секунд=%.2f ms\n", N, num_threads, elapsed_time);

    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    free(threads);
    free(thread_data);
}

void generate_plot() {
    FILE *plot_script = fopen("plot_results.py", "w");
    if (!plot_script) {
        perror("Ошибка создания plot script");
        return;
    }

    fprintf(plot_script, "import pandas as pd\n");
    fprintf(plot_script, "import matplotlib.pyplot as plt\n");
    fprintf(plot_script, "import seaborn as sns\n\n");
    fprintf(plot_script, "df = pd.read_csv('results.csv', header=None, names=['Size', 'Threads', 'Time'])\n");
    fprintf(plot_script, "pivoted = df.pivot(index='Size', columns='Threads', values='Time')\n\n");
    fprintf(plot_script, "plt.figure(figsize=(12, 8))\n");
    fprintf(plot_script, "for column in pivoted.columns:\n");
    fprintf(plot_script, "    plt.plot(pivoted.index, pivoted[column], label=f'{column} Потоки', marker='o')\n\n");
    fprintf(plot_script, "plt.xlabel('Размер')\n");
    fprintf(plot_script, "plt.ylabel('Время (ms)')\n");
    fprintf(plot_script, "plt.title('Тестирование потоков')\n");
    fprintf(plot_script, "plt.legend()\n");
    fprintf(plot_script, "plt.grid(True)\n");
    fprintf(plot_script, "plt.savefig('performance_plot.png')\n");
    fprintf(plot_script, "plt.show()\n");
    fclose(plot_script);

    printf("Сохранено в 'performance_plot.png'\n");
}

int main() {
    printf("Тестирование...\n");
    
    FILE *results_file = fopen("results.csv", "w");
    if (!results_file) {
        perror("Ошибка создания results file");
        return 1;
    }


    for (int size = STEP_SIZE; size <= MAX_SIZE; size += STEP_SIZE) {
        for (int threads = 1; threads <= MAX_THREADS; threads *= THREAD_STEP) {
            run_test(size, threads, results_file);
        }
    }

    fclose(results_file);
    printf("\nСохранено в'results.csv'\n");

    generate_plot();

    return 0;
}
![alt text](perfomance_plog.png)

