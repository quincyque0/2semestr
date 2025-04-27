#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>

#define MAX_THREADS 128
#define MAX_SIZE 2500
#define STEP_SIZE 500
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
    printf("N=%d, Threads=%d, Time=%.2f ms\n", N, num_threads, elapsed_time);

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
        perror("Failed to create plot script");
        return;
    }

    fprintf(plot_script, "import pandas as pd\n");
    fprintf(plot_script, "import matplotlib.pyplot as plt\n");
    fprintf(plot_script, "import seaborn as sns\n\n");
    fprintf(plot_script, "df = pd.read_csv('results.csv', header=None, names=['Size', 'Threads', 'Time'])\n");
    fprintf(plot_script, "pivoted = df.pivot(index='Size', columns='Threads', values='Time')\n\n");
    fprintf(plot_script, "plt.figure(figsize=(12, 8))\n");
    fprintf(plot_script, "for column in pivoted.columns:\n");
    fprintf(plot_script, "    plt.plot(pivoted.index, pivoted[column], label=f'{column} threads', marker='o')\n\n");
    fprintf(plot_script, "plt.xlabel('Matrix Size')\n");
    fprintf(plot_script, "plt.ylabel('Time (ms)')\n");
    fprintf(plot_script, "plt.title('Matrix Multiplication Performance')\n");
    fprintf(plot_script, "plt.legend()\n");
    fprintf(plot_script, "plt.grid(True)\n");
    fprintf(plot_script, "plt.savefig('performance_plot.png')\n");
    fprintf(plot_script, "plt.show()\n");
    fclose(plot_script);

    printf("Running Python script to generate plot...\n");
    system("python3 plot_results.py");
    printf("Plot saved as 'performance_plot.png'\n");
}

int main() {
    printf("Starting matrix multiplication performance tests...\n");
    
    FILE *results_file = fopen("results.csv", "w");
    if (!results_file) {
        perror("Failed to create results file");
        return 1;
    }


    for (int size = STEP_SIZE; size <= MAX_SIZE; size += STEP_SIZE) {
        for (int threads = 1; threads <= MAX_THREADS; threads *= THREAD_STEP) {
            run_test(size, threads, results_file);
        }
    }

    fclose(results_file);
    printf("\nAll tests completed. Results saved to 'results.csv'\n");

    generate_plot();
    //gcc matrix_mult.c -o matrix_mult -pthread -lm && ./matrix_mult

    return 0;
}