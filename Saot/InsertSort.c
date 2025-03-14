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
void ShellSort(int A[],int n, int *ptr_cf, int *ptr_mf){

}

void createDotFileTablic(const char *filename, int *Tablic) {
    FILE *file = fopen(filename, "w");

    fprintf(file, "digraph G {\n");
    fprintf(file, "  node [shape=plaintext];\n");

    fprintf(file, "  table [label=<\n");
    fprintf(file, "    <table border='1' cellborder='1' cellspacing='0'>\n");

    fprintf(file, "      <tr>\n");
    fprintf(file, "        <td>N</td>\n");
    fprintf(file, "        <td>M+C</td>\n");
    fprintf(file, "        <td>исх(убыв свккакакак)</td>\n");
    fprintf(file, "        <td>исх(случ)</td>\n");
    fprintf(file, "        <td>исх(воз)</td>\n");
    fprintf(file, "      </tr>\n");

    for (int i = 0; i < 25; i += 5) {
        fprintf(file, "      <tr>\n");
        fprintf(file, "        <td>%d</td>\n", Tablic[i]); 
        fprintf(file, "        <td>%d</td>\n", Tablic[i + 1]);
        fprintf(file, "        <td>%d</td>\n", Tablic[i + 2]); 
        fprintf(file, "        <td>%d</td>\n", Tablic[i + 3]);
        fprintf(file, "        <td>%d</td>\n", Tablic[i + 4]); 
        fprintf(file, "      </tr>\n");
    }


    fprintf(file, "    </table>\n");
    fprintf(file, "  >];\n");
    fprintf(file, "}\n");

    fclose(file);
}


void createDotFileTablic2(const char *filename, int *Tablic) {
    FILE *file = fopen(filename, "w");

    fprintf(file, "digraph G {\n");
    fprintf(file, "  node [shape=plaintext];\n");


    fprintf(file, "  table [label=<\n");
    fprintf(file, "    <table border='1' cellborder='1' cellspacing='0'>\n");


    fprintf(file, "      <tr>\n");
    fprintf(file, "        <td>N</td>\n");
    fprintf(file, "        <td>Select</td>\n");
    fprintf(file, "        <td></td>\n");
    fprintf(file, "        <td>Shaker</td>\n");
    fprintf(file, "        <td>Insert</td>\n");
    fprintf(file, "      </tr>\n");

   
    for (int i = 0; i < 25; i += 5) {
        fprintf(file, "      <tr>\n");
        fprintf(file, "        <td>%d</td>\n", Tablic[i]);  
        fprintf(file, "        <td>%d</td>\n", Tablic[i + 1]); 
        fprintf(file, "        <td>%d</td>\n", Tablic[i + 2]);  
        fprintf(file, "        <td>%d</td>\n", Tablic[i + 3]);
        fprintf(file, "        <td>%d</td>\n", Tablic[i + 4]);  
        fprintf(file, "      </tr>\n");
    }


    fprintf(file, "    </table>\n");
    fprintf(file, "  >];\n");
    fprintf(file, "}\n");

    fclose(file);
    printf("DOT-файл создан: %s\n", filename);
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
    printf("N\t\tSelect\t\tBouble\t\tShaker\t\tInsert\n");
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[0],Tablic[1],Tablic[2],Tablic[3],Tablic[4]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[5],Tablic[6],Tablic[7],Tablic[8],Tablic[9]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[10],Tablic[11],Tablic[12],Tablic[13],Tablic[14]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[15],Tablic[16],Tablic[17],Tablic[18],Tablic[19]);
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",Tablic[20],Tablic[21],Tablic[22],Tablic[23],Tablic[24]);
}



void insertSort( int A[],int n, int *ptr_cf, int *ptr_mf){
    *ptr_mf = 0;
    *ptr_cf = 0;

    for(int i = 1; i < n; i++){
        int t = A[i];
        int j = i - 1;
        (*ptr_mf)++;
        while(j >= 0){
            (*ptr_cf)++;
            if(t < A[j]){
                A[j+1] = A[j];
                (*ptr_mf)++;
                j--;
            }else break;
        }
        A[j+1] = t;
        (*ptr_mf)++;
    }
} 


void gnuReader() {
    FILE *file = fopen("data1.txt", "w"); 
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return;
    }

    fprintf(file, "N\tSelectSort\tBubbleSort\tShakerSort\tInsertSort\n");

    for (int i = 1; i <= 500; i++) {
        int *A = (int*)malloc(sizeof(int) * i);
        int *B = (int*)malloc(sizeof(int) * i);
        int *C = (int*)malloc(sizeof(int) * i);
        int *D = (int*)malloc(sizeof(int) * i);

        FillRand(i, A);
        FillRand(i, B);
        FillRand(i, C);
        FillRand(i, D);

        int sec = 0, sem = 0; 
        int bc = 0, bm = 0;   
        int sc = 0, sm = 0;   
        int ic = 0, im = 0;  

        selectSortGrade(A, i, &sec, &sem);
        boubleSort(B, i, &bc, &bm);
        shakerSort(C, i, &sc, &sm);
        insertSort(D, i, &ic, &im);


        fprintf(file, "%d\t%d\t%d\t%d\t%d\n", i, sec + sem, bc + bm, sc + sm, ic + im);
       
        free(A);
        free(B);
        free(C);
        free(D);
    }

    fclose(file);

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    fprintf(gnuplotPipe, "set title 'Сравнение трудоемкости сортировок'\n");
    fprintf(gnuplotPipe, "set xlabel 'Размер массива (N)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Трудоемкость (T)'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "plot 'data1.txt' using 1:2 with lines title 'SelectSort', \\\n");
    fprintf(gnuplotPipe, "'data1.txt' using 1:3 with lines title 'BubbleSort', \\\n");
    fprintf(gnuplotPipe, "'data1.txt' using 1:4 with lines title 'ShakerSort', \\\n");
    fprintf(gnuplotPipe, "'data1.txt' using 1:5 with lines title 'InsertSort'\n");
    fprintf(gnuplotPipe, "set terminal png size 2400,1600\n");
    fprintf(gnuplotPipe, "set output 'sort_graph.png'\n");
    fprintf(gnuplotPipe, "replot\n");
    fprintf(gnuplotPipe, "exit\n");

    pclose(gnuplotPipe);
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
        int max_theoretical_comparisons = ((N * N) - N) / 4;
        int min_theoretical_comparisons = N-1;
        int m_theoretical_comparisons = (N*N-N)/4;
        int theoretical_swaps_max = (((N * N) - N) / 4) + N - 1;

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
        
        //-------------------shellSort-----------------------------


        FillDie(N, N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int BsortDOWN = comparisons+swaps;
    
        Filllne(1, N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int BsortUP = comparisons+swaps;

        FillRand(N , A);
        shakerSort(A, N, &comparisons, &swaps);
        int BsortRAND = comparisons+swaps;



        // Tablic_Add5(&cur,Tablic_Znach,N,m_theoretical_comparisons+theoretical_swaps_max,IsortDOWN,IsortRAND,IsortUP);
        // Tablic_Add5(&cur2,Tablic_Znach2,N,SesortRAND,BsortRAND,SsortRAND,IsortRAND);

    }
    
    Tablic(Tablic_Znach);
    printf("\n\n");
    Tablic2(Tablic_Znach2);

FILE *file1 = fopen("data1.txt", "w");
FILE *file2 = fopen("data2.txt", "w");

if (file1 == NULL || file2 == NULL) {
    printf("Ошибка открытия файла!\n");
    return 1;
}


for (int i = 0; i < 25; i += 5) {
    fprintf(file1, "%d\t%d\t%d\t%d\t%d\n", Tablic_Znach[i], Tablic_Znach[i+1], Tablic_Znach[i+2], Tablic_Znach[i+3], Tablic_Znach[i+4]);
}


for (int i = 0; i < 25; i += 5) {
    fprintf(file2, "%d\t%d\t%d\t%d\t%d\n", Tablic_Znach2[i], Tablic_Znach2[i+1], Tablic_Znach2[i+2], Tablic_Znach2[i+3], Tablic_Znach2[i+4]);
}

fclose(file1);
fclose(file2);
createDotFileTablic("tablic.dot", Tablic_Znach);
createDotFileTablic2("tablic2.dot", Tablic_Znach2);
system("dot -Tpng tablic.dot -o tablic.png");
system("dot -Tpng tablic2.dot -o tablic2.png");
system("open tablic.png");
system("open tablic2.png");
gnuReader();
}