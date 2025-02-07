#include<stdio.h>

int main(){
    int n, s;
    scanf("%d %d",&n , &s);

    char mas[n+1];
    scanf("%s", mas);
    for(int i = 0; i < s; i++){
        for (int j = 0;j < n -1;j++){
            if(mas[j] == 'B' && mas[j + 1] == 'G'){
                char tmp = mas[j];
                mas[j] = mas[j+1];
                mas[j+1] = tmp;
                j++;
            }
        }
    }
}