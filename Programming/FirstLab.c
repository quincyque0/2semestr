#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

struct student{
    char *name;
    int math;
    int phys;
    int info;
    int TotalScore;

};

struct student addStudent(char* name, int mat, int phy, int inf) {
    struct student newStudent;
    newStudent.name = strdup(name);
    newStudent.math = mat;
    newStudent.phys = phy;
    newStudent.info = inf;
    newStudent.TotalScore = newStudent.math + newStudent.phys + newStudent.info;
    return newStudent;
}


void printStudentInfo(struct student stud){
    printf("Name:%s M:%d P:%d I:%d Toral:%d\n",stud.name,stud.math,stud.phys,stud.info,stud.TotalScore);
}


char* generateRandomName(){
char *spisnames[] = {
        "Абакум", "Абрам", "Абросим", "Аввакум", "Август", "Авдей", "Авдий", "Авель", "Авенир", "Аверий",
        "Аверкий", "Аверьян", "Авксентий", "Авраам", "Авраамий", "Аврам", "Аврамий", "Аврелиан", "Автоном", "Агап",
        "Агапий", "Агапит", "Агафангел", "Агафон", "Аггей", "Адам", "Адриан", "Азар", "Азарий", "Акакий",
        "Акила", "Аким", "Акиндин", "Акинф", "Акинфий", "Аксён", "Аксентий", "Александр", "Алексей", "Алексий",
        "Альберт", "Альфред", "Амвросий", "Амос", "Амфилохий", "Ананий", "Анастасий", "Анатолий", "Андрей", "Андриан",
        "Андрон", "Андроний", "Андроник", "Анект", "Анемподист", "Аникей", "Аникий", "Аникита", "Анисий", "Анисим",
        "Антиох", "Антип", "Антипа", "Антипий", "Антон", "Антонин", "Антроп", "Антропий", "Ануфрий", "Аполлинарий",
        "Аполлон", "Аполлос", "Ардалион", "Ареф", "Арефий", "Арий", "Аристарх", "Аристид", "Аркадий", "Арнольд",
        "Арон", "Арсен", "Арсений", "Арсентий", "Артамон", "Артём", "Артемий", "Артур", "Архип", "Асаф",
        "Асафий", "Аскольд", "Афанасий", "Афиноген", "Афинодор", "Африкан", "Бажен", "Бенедикт", "Богдан", "Болеслав",
        "Бонифат", "Бонифатий", "Борис", "Борислав", "Бронислав", "Будимир", "Вавила", "Вадим", "Валентин", "Валериан"
    };
    int numNames = sizeof(spisnames) / sizeof(spisnames[0]);
    return spisnames[rand() % numNames];

}
int partition(int low, int high, struct student arr[]);

void quickSort(int low, int high, struct student arr[]) {
    
    if (low < high) {
        int pivot_index = partition(low, high, arr); //Разделение массива

        quickSort(low, pivot_index - 1, arr); //Рекурсивная сортировка левой части
        quickSort(pivot_index + 1, high, arr); //Рекурсивная сортировка правой части
    }

}


int partition(int low, int high, struct student arr[]) {
    int pivot = arr[high].TotalScore;  // Опорный элемент
    int i = low - 1;    // Индекс меньшего элемента
    struct student temp;

    for (int j = low; j <= high - 1; j++) {// Если текущий элемент меньше или равен опорному

        if (arr[j].TotalScore <= pivot) {
            i++;    


            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
    
}
void selectionSort(struct student arr[], int n) {
    int min;
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for (int i = 0; i < n - 1; i++) {

        min = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].TotalScore < arr[min].TotalScore)
                min = j;


        if (min != i) {
            struct student temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
    end = clock(); 

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;   // Вычисляем время в секундах

    printf("Время работы процессора: %f секунд\n ; размер данных : %ld бит\n" , cpu_time_used , N*sizeof(struct student));
}

void radixSort(struct student arr[], int n) {
    int maxNumber = 0;
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    for (int i = 0; i < n; i++) {
        if (maxNumber < arr[i].TotalScore)
            maxNumber = arr[i].TotalScore;
    }

    
    struct student **buckets = (struct student **)malloc(10 * sizeof(struct student *));
    for (int i = 0; i < 10; i++) {
        buckets[i] = (struct student *)malloc(n * sizeof(struct student));
    }

    int *bucketCounts = (int *)malloc(10 * sizeof(int)); 
    struct student *tempArr = (struct student *)malloc(n * sizeof(struct student));

    // Сортируем по каждому разряду, начиная с наименьшего
    for (int raz = 1; maxNumber / raz > 0; raz *= 10) {
        // Обнуляем счетчики bucketCounts
        for (int i = 0; i < 10; i++) {
            bucketCounts[i] = 0;
        }

        // Распределяем элементы по buckets в соответствии со значением текущего разряда
        for (int i = 0; i < n; i++) {
            int digit = (arr[i].TotalScore / raz) % 10;
            buckets[digit][bucketCounts[digit]] = arr[i];
            bucketCounts[digit]++;
        }

        // Собираем элементы из buckets обратно в исходный массив
        int index = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < bucketCounts[i]; j++) {
                arr[index] = buckets[i][j];
                index++;
            }
        }
    }


    for(int i = 0; i < 10; i++) {
        free(buckets[i]);
    }
    free(buckets);
    free(bucketCounts);
    free(tempArr);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;   // Вычисляем время в секундах

    printf("Время работы процессора: %f секунд\nразмер данных : %ld бит\n" , cpu_time_used , N*sizeof(struct student));
}

void printProcessorInfoViaSystem() {
    // SUDO POWERMETRICS для поиска данных о процесоре на mac
    // system("grep -E 'model name|cpu MHz' /proc/cpuinfo | head -2");
    system("sysctl -n machdep.cpu.brand_string");
}


int main(){
    struct student students[N];
    srand(time(NULL));
    for (int i = 0; i < N; i++) { 
        
        char *name = generateRandomName();
        int math = rand() % 101;
        int phy = rand() % 101;
        int inf = rand() % 101;
        students[i] = addStudent(name, math, phy, inf);
    }

    
    
    printf("Список студентов до сортировки:\n");
    // for (int i = 0; i < N; i++) {
    //     printStudentInfo(students[i]);
    // }
    // printf("\n\n");
    

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    quickSort(0,N-1,students);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;   // Вычисляем время в секундах
    printf("Время работы процессора: %f секунд\n ; размер данных : %ld бит\n\n" , cpu_time_used , N*sizeof(struct student));

    // radixSort(students,N);

    // selectionSort(students,N);

    printf("Список студентов после сортировки:\n");
    // for (int i = 0; i < N; i++) {
    //     printStudentInfo(students[i]);
    // }
    // printf("\n\n");

    printProcessorInfoViaSystem();
    
}



