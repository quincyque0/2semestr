#include<stdio.h>
int main(){
    int n;
    int x = 0;
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        char com[3];
        scanf("%s", com);

        if (com[1] == '+')
        {
            x++;
        }
        else x--;
    }
    printf("%d",x);
}