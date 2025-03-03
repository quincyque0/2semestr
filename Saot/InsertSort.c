#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int* Filllne(int begin,int size,int *massive){
    for(int i = 0; i < size; i++){
        massive[i] = begin + i;
    }
    return massive;
}

int* FillDie(int begin,int size,int *massive){
    for(int i = 0; i < size ;i++){
        massive[i] = begin - i;
    }
    return massive;
}

void Printer(int *arr, int size){
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int* FillRand(int size, int *massive){
    for(int i = 0; i < size; i++){
        massive[i] = rand() % 10000000;
    }
    return massive;
}
void Tablic_Add7(int *cur, int *tablic, int A,int B,int C,int D,int E,int F,int G){
    tablic[*cur] = A;
    tablic[*cur+1] = B;
    tablic[*cur+2] = C;
    tablic[*cur+3] = D;
    tablic[*cur+4] = E;
    tablic[*cur+5] = F;
    tablic[*cur+6] = G;
    *cur += 7;
}
void Tablic_Add5(int *cur, int *tablic, int A,int B,int C,int D,int E){
    tablic[*cur] = A;
    tablic[*cur+1] = B;
    tablic[*cur+2] = C;
    tablic[*cur+3] = D;
    tablic[*cur+4] = E;
    *cur += 5;
}

void Tablic(int *Tablic){
    printf("N\t\tM+C\t\tисх(убыв)\tисх(случ)\tисх(воз)\n");
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[0],Tablic[1],Tablic[2],Tablic[3],Tablic[4]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[5],Tablic[6],Tablic[7],Tablic[8],Tablic[9]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[10],Tablic[11],Tablic[12],Tablic[13],Tablic[14]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[15],Tablic[16],Tablic[17],Tablic[18],Tablic[19]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[20],Tablic[21],Tablic[22],Tablic[23],Tablic[24]);
}
void Tablic2(int *Tablic){
    printf("N\t\tSelest\t\tBouble\t\tShaker\t\tInsert\n");
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[0],Tablic[1],Tablic[2],Tablic[3],Tablic[4]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[5],Tablic[6],Tablic[7],Tablic[8],Tablic[9]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[10],Tablic[11],Tablic[12],Tablic[13],Tablic[14]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[15],Tablic[16],Tablic[17],Tablic[18],Tablic[19]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[20],Tablic[21],Tablic[22],Tablic[23],Tablic[24]);
}



void insertSort(int arr[], int n, int *comparisons, int *swaps){
    int  t, j;
    *comparisons = 0;
    *swaps = 0;
    for(int i = 1; i < n; i++){
        (*swaps)++;t = arr[i]; j = i - 1;
        (*comparisons)++;while(j > 0 && t < arr[j]){
            arr[j+1] = arr[j];
            (*swaps)++;
            j = j - 1;
        }
        arr[j+1] = t;
        (*swaps)++;
    }
}
void selectSortGrade(int arr[], int n, int *comparisons, int *swaps) {
    int i, j, min_idx, temp;

    *comparisons = 0;
    *swaps = 0;

    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            (*swaps)+=3;
        }
        // temp = arr[i];
        // arr[i] = arr[min_idx];
        // arr[min_idx] = temp;
        // (*swaps)+=3;
    }
}
void shakerSort(int *arr, int size,int *comparisons, int *swaps){
    int l = 0,r = size-1, k = size,tmp;
    *comparisons = 0;
    *swaps = 0;
    do{
        for(int i = r; i > l;i--){
            (*comparisons)++;if(arr[i] < arr[i-1]){
                tmp = arr[i];
                arr[i]=arr[i-1];
                arr[i-1]=tmp;
                k=i;
                (*swaps) += 3;

            }
        }
        l=k;
        for(int j = l; j < r;j++){
            (*comparisons)++;if(arr[j] >arr[j+1]){
                tmp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=tmp;
                k=j;
                (*swaps) += 3;

            }
        }
        r=k;

    }while(l<r);

}
void boubleSort(int *arr, int size, int *comparisons, int *swaps){
    int tmp;
    *comparisons = 0;
    *swaps = 0;
    for(int i = 0; i < size - 1; i++){
        for(int j = size - 1; j > i; j--){
            (*comparisons)++; if(arr[j] < arr[j-1]){
                tmp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = tmp;
                (*swaps) += 3;
            }
        }
    }
}
void gnuReader() {
    FILE *file = fopen("data1.txt", "w"); // Файл для сохранения данных
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return;
    }

    // Заголовок файла
    fprintf(file, "N\tSelectSort\tBubbleSort\tShakerSort\tInsertSort\n");

    for (int i = 1; i <= 500; i++) {
        int *A = (int*)malloc(sizeof(int) * i);
        int *B = (int*)malloc(sizeof(int) * i);
        int *C = (int*)malloc(sizeof(int) * i);
        int *D = (int*)malloc(sizeof(int) * i);

        // Заполняем массивы случайными данными
        FillRand(i, A);
        FillRand(i, B);
        FillRand(i, C);
        FillRand(i, D);

        int sec = 0, sem = 0; // SelectSort
        int bc = 0, bm = 0;   // BubbleSort
        int sc = 0, sm = 0;   // ShakerSort
        int ic = 0, im = 0;   // InsertSort

        // Выполняем сортировки
        selectSortGrade(A, i, &sec, &sem);
        boubleSort(B, i, &bc, &bm);
        shakerSort(C, i, &sc, &sm);
        insertSort(D, i, &ic, &im);

        // Записываем данные в файл
        fprintf(file, "%d\t%d\t%d\t%d\t%d\n", i, sec + sem, bc + bm, sc + sm, ic + im);

        // Освобождаем память
        free(A);
        free(B);
        free(C);
        free(D);
    }

    fclose(file);
    printf("Данные сохранены в файл data1.txt\n");

    // Вызов gnuplot для построения графиков
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        printf("Ошибка вызова gnuplot!\n");
        return;
    }

    // Скрипт для gnuplot
    fprintf(gnuplotPipe, "set title 'Сравнение трудоемкости сортировок'\n");
    fprintf(gnuplotPipe, "set xlabel 'Размер массива (N)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Трудоемкость (T)'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "plot 'data1.txt' using 1:2 with lines title 'SelectSort', \\\n");
    fprintf(gnuplotPipe, "     'data1.txt' using 1:3 with lines title 'BubbleSort', \\\n");
    fprintf(gnuplotPipe, "     'data1.txt' using 1:4 with lines title 'ShakerSort', \\\n");
    fprintf(gnuplotPipe, "     'data1.txt' using 1:5 with lines title 'InsertSort'\n");
    fprintf(gnuplotPipe, "set terminal png size 2400,1600\n");
    fprintf(gnuplotPipe, "set output 'sort_graph.png'\n");
    fprintf(gnuplotPipe, "replot\n");
    fprintf(gnuplotPipe, "exit\n");

    pclose(gnuplotPipe);
    printf("График сохранен в файл sort_graph.png\n");
}
    
int main(){
int N = 100;
    srand(time(NULL));
    int *A = (int*)malloc(sizeof(int) * 500);
    int *Tablic_Znach = (int*)malloc(sizeof(int) * 25);
    int *Tablic_Znach2 = (int*)malloc(sizeof(int) * 25);
    int comparisons, swaps ,cur = 0,cur2 = 0;
    
    for(int N = 100; N <= 500 ; N += 100 ){
        // ---------------insertSort-----------------------

        int theoretical_swaps_orderly = 2*(N-1);
        int theoretical_swaps_random = 3* ((N * N) - N) / 4;
        int max_theoretical_comparisons = ((N * N) - N) / 2;
        int min_theoretical_comparisons = N-1;
        int theoretical_swaps_max = (((N * N) - N) / 2) + 2*N - 2;

        FillDie(N, N , A);
        insertSort(A, N, &comparisons, &swaps);
        printf("N : %d",N);
        printf("Теоретическое количество сравнений(%d), перестановок (%d)\n", max_theoretical_comparisons, theoretical_swaps_max);
        printf("Фактическое количество сравнений: %d\n", comparisons);
        printf("Фактическое количество переcтановок: %d\n", swaps);
        printf("Трудоёмкость сортировки(T) = %d \n\n",swaps + comparisons);
        int IsortDOWN = comparisons+swaps;
        
        Filllne(1, N , A);
        insertSort(A, N, &comparisons, &swaps);
        printf("N : %d",N);
        printf("Теоретическое количество сравнений(%d), перестановок (%d)\n", max_theoretical_comparisons, theoretical_swaps_max);
        printf("Фактическое количество сравнений: %d\n", comparisons);
        printf("Фактическое количество переcтановок: %d\n", swaps);
        printf("Трудоёмкость сортировки(T) = %d \n\n",swaps + comparisons);
        int IsortUP = comparisons+swaps;

        FillRand(N , A);
        insertSort(A, N, &comparisons, &swaps);
        printf("N : %d",N);
        printf("Теоретическое количество сравнений(%d), перестановок(Ср) (%d)\n", max_theoretical_comparisons, theoretical_swaps_max);
        printf("Фактическое количество сравнений: %d\n", comparisons);
        printf("Фактическое количество переcтановок: %d\n", swaps);
        printf("Трудоёмкость сортировки(T) = %d \n\n",swaps + comparisons);
        int IsortRAND = comparisons+swaps;
        
        //-------------------shakerSort-----------------------------

        FillDie(N, N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int SsortDOWN = comparisons+swaps;
    
        Filllne(1, N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int SsortUP = comparisons+swaps;

        FillRand(N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int SsortRAND = comparisons+swaps;
        //-------------------seletcSort-----------------------------

        FillDie(N, N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int SesortDOWN = comparisons+swaps;
    
        Filllne(1, N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int SesortUP = comparisons+swaps;

        FillRand(N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int SesortRAND = comparisons+swaps;
        //-------------------boubleSort-----------------------------

        FillDie(N, N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int BsortDOWN = comparisons+swaps;
    
        Filllne(1, N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int BsortUP = comparisons+swaps;

        FillRand(N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int BsortRAND = comparisons+swaps;



        Tablic_Add5(&cur,Tablic_Znach,N,max_theoretical_comparisons+theoretical_swaps_max,IsortDOWN,IsortRAND,IsortUP);
        Tablic_Add5(&cur2,Tablic_Znach2,N,SesortRAND,BsortRAND,SsortRAND,IsortRAND);

    }
    
    Tablic(Tablic_Znach);
    printf("\n\n");
    Tablic2(Tablic_Znach2);
    // Сохранение данных в файл для gnuplot
FILE *file1 = fopen("data1.txt", "w");
FILE *file2 = fopen("data2.txt", "w");

if (file1 == NULL || file2 == NULL) {
    printf("Ошибка открытия файла!\n");
    return 1;
}

// Запись данных из Tablic_Znach
for (int i = 0; i < 25; i += 5) {
    fprintf(file1, "%d\t%d\t%d\t%d\t%d\n", Tablic_Znach[i], Tablic_Znach[i+1], Tablic_Znach[i+2], Tablic_Znach[i+3], Tablic_Znach[i+4]);
}

// Запись данных из Tablic_Znach2
for (int i = 0; i < 25; i += 5) {
    fprintf(file2, "%d\t%d\t%d\t%d\t%d\n", Tablic_Znach2[i], Tablic_Znach2[i+1], Tablic_Znach2[i+2], Tablic_Znach2[i+3], Tablic_Znach2[i+4]);
}

fclose(file1);
fclose(file2);
gnuReader();
}