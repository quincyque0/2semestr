#include<stdio.h>
#include<string.h>

int main(){
    int n;

    scanf("%d",&n);

    for(int i = 0;i < n; i++){
        int k;
        scanf("%d",&k);
        int count = k;
        int size_uniq = 0;
        char s[k];
        char uniq[k];
        
        scanf("%s",s);
        for (int j =0 ; j< k; j++){
            int yes =0;
            for(int q = 0; q < size_uniq;q++){
                if(uniq[q]  == s[j]){
                    yes = 1;
                    break;
                }
            
                
            }
            if(yes == 0){
                    count++;
                    uniq[size_uniq++] = s[j];
                }


        }
        printf("%d",count);

    }
}