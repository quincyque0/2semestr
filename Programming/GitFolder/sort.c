void selectSortGrade(int arr[], int n) {
    int i, j, min_idx, temp;



    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {

            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;

        }
        // temp = arr[i];
        // arr[i] = arr[min_idx];
        // arr[min_idx] = temp;
        // (*swaps)+=3;
    }
}int main()
{

int a[] = {4, 2};
selectSortGrade(a,2);
}