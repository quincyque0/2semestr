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