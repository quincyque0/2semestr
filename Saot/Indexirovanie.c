#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct phone_book{
    char name[50];
    char surname[50];
    char patronymic[50];
    int phonenumber;
};

int* Filllne(int begin,int size,int *massive){
    for(int i = 0; i < size; i++){
        massive[i] = begin + i;
    }
    return massive;
}


int Less(struct phone_book A, struct phone_book B){
    return strcmp(A.name, B.name) < 0;
}

int More(struct phone_book A, struct phone_book B){
    return strcmp(A.name, B.name) > 0;
}

void indexprint(struct phone_book arr[],int index[],int size){
    for(int i = 0; i < size; i++) {
        printf("%s %s %s %d\n", arr[index[i]].name, arr[index[i]].surname, 
            arr[index[i]].patronymic, arr[index[i]].phonenumber);
    }
}
void Shaker_sort(struct phone_book arr[], int sizestruct, int index[]){
    int L = 0, R = sizestruct - 1, k = sizestruct - 1;
    do{
        int tmp;
        for(int i = R; i > L; i--){
            if(Less(arr[i], arr[i-1])){
                tmp = index[i];
                index[i] = index[i-1];
                index[i-1] = tmp;
                k = i;
            }
        }
        L = k;
        for(int i = L; i < R; i++){
            if (More(arr[i], arr[i+1])){
                tmp = index[i];
                index[i] = index[i+1];
                index[i+1] = tmp;
                k = i;
            }
        }
        R = k;
    } while(L < R);
}

int main(){

    
    struct phone_book directory[] = {
        {"Swifter","Phperov","Cssovich",9136655},
        {"VanGO","Pascalev","Asemblerovich",7770099},
        {"Javio","Delphino","Binarycodovich",1234321},
        {"Cplus","Phperov","Htmlovich",8803306},
        {"Swifter","Typescriptov","Asemblerovich",8803306},
    };
    
    int size = sizeof(directory)/sizeof(directory[0]);

    int *index_name = malloc(size * sizeof(int));
    int *index_surname = malloc(size * sizeof(int));

    Filllne(0,size,index_name);
    Filllne(0,size,index_surname);

    Shaker_sort(directory, size,index_name);

    for(int i = 0;i < size; i++){
        printf("%d\n",index_name[i]);
    }
    for(int i = 0; i < size; i++) {
        printf("%s %s %s %d\n", directory[i].name, directory[i].surname, 
               directory[i].patronymic, directory[i].phonenumber);
    }
    printf("\n");    

    indexprint(directory,index_name,size);
    
    return 0;
}