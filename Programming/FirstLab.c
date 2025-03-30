#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 10

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
        int pivot_index = partition(low, high, arr); 

        quickSort(low, pivot_index - 1, arr);
        quickSort(pivot_index + 1, high, arr); 
    }

}


int partition(int low, int high, struct student arr[]) {
    int curr;
    int pivot = arr[high].math; 
    int i = low - 1;    
    struct student temp;
    printf("enter sort index\n1 - Phys\n2 - Math\n3 - Info\n4 - Total");
    scanf("%d",&curr);
    switch (curr)
    {
    case 4:
 

        for (int j = low; j <= high - 1; j++) {

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
        break;
    case 2:


        for (int j = low; j <= high - 1; j++) {

            if (arr[j].phys <= pivot) {
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
        break;
    case 3:

        for (int j = low; j <= high - 1; j++) {

            if (arr[j].info <= pivot) {
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
        break;
    case 1:

        for (int j = low; j <= high - 1; j++) {

            if (arr[j].math <= pivot) {
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
        break;
    default:
    perror("wrong enter");
        break;
    }
        
    return 0;
}
void selectionSort(struct student arr[], int n) {
    int min;
    int curr;
    clock_t start, end;
    double cpu_time_used;
    printf("enter sort index\n1 - Phys\n2 - Math\n3 - Info\n4 - Total");
    scanf("%d",&curr);
    start = clock();
    
    switch (curr)
    {
    case 1:
        for (int i = 0; i < n - 1; i++) {

        min = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].math < arr[min].math)
                min = j;


        if (min != i) {
            struct student temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
        break;
    case 2:
        for (int i = 0; i < n - 1; i++) {

        min = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].phys < arr[min].phys)
                min = j;


        if (min != i) {
            struct student temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
    case 3:
        for (int i = 0; i < n - 1; i++) {

        min = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].info < arr[min].info)
                min = j;


        if (min != i) {
            struct student temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
    case 4:
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
    default:
        perror("wrong enter");
        break;
    }
    
    end = clock(); 

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;   

    printf("Время работы процессора: %f секунд\n ; размер данных : %ld бит\n" , cpu_time_used , N*sizeof(struct student));
}

void radixSort(struct student arr[], int n) {
    int curr;
    int maxNumber = 0;
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    printf("enter sort index\n1 - Phys\n2 - Math\n3 - Info\n4 - Total");
    scanf("%d",&curr);
    if(curr == 1){
        for (int i = 0; i < n; i++) {
            if (maxNumber < arr[i].phys)
                maxNumber = arr[i].phys;
        }
    }
    else if(curr == 2){
        for (int i = 0; i < n; i++) {
            if (maxNumber < arr[i].math)
                maxNumber = arr[i].math;
        }
    }
    else if(curr == 3){
        for (int i = 0; i < n; i++) {
            if (maxNumber < arr[i].info)
                maxNumber = arr[i].info;
        }
    }
    else if(curr == 4){
        for (int i = 0; i < n; i++) {
            if (maxNumber < arr[i].TotalScore)
                maxNumber = arr[i].TotalScore;
        }
    }
    else perror("wrong enter");
   

    
    struct student **buckets = (struct student **)malloc(10 * sizeof(struct student *));
    for (int i = 0; i < 10; i++) {
        buckets[i] = (struct student *)malloc(n * sizeof(struct student));
    }

    int *bucketCounts = (int *)malloc(10 * sizeof(int)); 
    struct student *tempArr = (struct student *)malloc(n * sizeof(struct student));

    for (int raz = 1; maxNumber / raz > 0; raz *= 10) {
        for (int i = 0; i < 10; i++) {
            bucketCounts[i] = 0;
        }
        if(curr ==1){
            for (int i = 0; i < n; i++) {
                int digit = (arr[i].math / raz) % 10;
                buckets[digit][bucketCounts[digit]] = arr[i];
                bucketCounts[digit]++;
            }
        }
        if(curr == 2){
            for (int i = 0; i < n; i++) {
                int digit = (arr[i].phys / raz) % 10;
                buckets[digit][bucketCounts[digit]] = arr[i];
                bucketCounts[digit]++;
            }
        }
        if(curr == 3){
            for (int i = 0; i < n; i++) {
                int digit = (arr[i].info / raz) % 10;
                buckets[digit][bucketCounts[digit]] = arr[i];
                bucketCounts[digit]++;
            }
        }
        if(curr == 4){
            for (int i = 0; i < n; i++) {
                int digit = (arr[i].TotalScore / raz) % 10;
                buckets[digit][bucketCounts[digit]] = arr[i];
                bucketCounts[digit]++;
            }
        }

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

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  

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
    
    int sortsellect;
    clock_t start, end;
    double cpu_time_used;
    printf("choice sort\n1 - select\n2 - radix\n3 - quick");
    scanf("%d",&sortsellect);
    switch (sortsellect)
    {
    case 3:
        
        start = clock();
        quickSort(0,N-1,students);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  
        printf("Время работы процессора: %f секунд\n ; размер данных : %ld бит\n\n" , cpu_time_used , N*sizeof(struct student));
        break;
    case 1:
        selectionSort(students,N);
        break;
    case 2:
        radixSort(students,N);
        break;
    default:
        perror("wrong enter");
        break;
    }
    

    

    

    printf("Список студентов после сортировки:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }
    printf("\n\n");

    printProcessorInfoViaSystem();
    
}



