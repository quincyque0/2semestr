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
    }//daadadadadad
}