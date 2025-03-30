#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h> // для strcmp

struct phone_book{
    char name[50];
    char surname[50];
    char patronymic[50];
    int phonenumber;
};

int Less(struct phone_book A, struct phone_book B){
    return strcmp(A.name, B.name) < 0;
}

int More(struct phone_book A, struct phone_book B){
    return strcmp(A.name, B.name) > 0;
}

void Shaker_sort(struct phone_book arr[], int sizestruct){
    int L = 0, R = sizestruct - 1, k = sizestruct - 1;
    do{
        struct phone_book tmp;
        for(int i = R; i > L; i--){
            if(Less(arr[i], arr[i-1])){
                tmp = arr[i];
                arr[i] = arr[i-1];
                arr[i-1] = tmp;
                k = i;
            }
        }
        L = k;
        for(int i = L; i < R; i++){
            if (More(arr[i], arr[i+1])){
                tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
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
    Shaker_sort(directory, size);

    for(int i = 0; i < size; i++) {
        printf("%s %s %s %d\n", directory[i].name, directory[i].surname, 
               directory[i].patronymic, directory[i].phonenumber);
    }
    
    return 0;
}