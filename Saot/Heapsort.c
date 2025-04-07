#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int comparisonCount = 0;
int swapCount = 0;

void siftDownElement(int array[], int startIndex, int endIndex) {
    int currentValue = array[startIndex];
    int currentIndex = startIndex;

    while (1) {
        int childIndex = 2 * currentIndex;
        if (childIndex > endIndex) break;

        if (childIndex < endIndex) {
            if (array[childIndex + 1] > array[childIndex]) {
                comparisonCount++;
                childIndex = childIndex + 1;
            }
        }

        if (currentValue >= array[childIndex]) {
            comparisonCount++;
            break;
        }

        swapCount++;
        array[currentIndex] = array[childIndex];
        currentIndex = childIndex;
    }

    if (currentIndex != startIndex) swapCount++;
    swapCount++;
    array[currentIndex] = currentValue;
}

void buildMaxHeap(int array[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        siftDownElement(array, i, size - 1);
    }
}

void initializeArray(int array[], int size, int arrayType) {
    switch (arrayType) {
        case 0: 
            for (int i = 0; i < size; i++) array[i] = size - i;
            break;
        case 1: 
            for (int i = 0; i < size; i++) array[i] = rand() % (2 * size);
            break;
        case 2: 
            for (int i = 0; i < size; i++) array[i] = i + 1;
            break;
    }
}

void testHeapBuilding(int size) {
    int array[size];
    int theoreticalComplexity = 2 * log2(size) + log2(size) + 3;

    printf("| %5d ", size);

    for (int arrayType = 0; arrayType < 3; arrayType++) {
        initializeArray(array, size, arrayType);
        comparisonCount = swapCount = 0;
        siftDownElement(array, 1, size);
        printf("| %10d ", comparisonCount + swapCount);
    }

    printf("| %9d |\n", theoreticalComplexity);
}

void heapify(int array[], int rootIndex, int endIndex) {
    int root = rootIndex;

    while (2 * root + 1 <= endIndex) {
        int leftChild = 2 * root + 1;
        int swapIndex = root;

        comparisonCount++;
        if (array[swapIndex] < array[leftChild]) {
            swapIndex = leftChild;
        }

        if (leftChild + 1 <= endIndex) {
            comparisonCount++;
            if (array[swapIndex] < array[leftChild + 1]) {
                swapIndex = leftChild + 1;
            }
        }

        if (swapIndex == root) {
            return;
        } else {
            swapCount++;
            int temp = array[root];
            array[root] = array[swapIndex];
            array[swapIndex] = temp;
            root = swapIndex;
        }
    }
}

void performHeapSort(int array[], int size) {
    comparisonCount = swapCount = 0;

  
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(array, i, size - 1);
    }

 
    for (int i = size - 1; i > 0; i--) {
        swapCount++;
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        heapify(array, 0, i - 1);
    }
}

void testSortingPerformance(int size) {
    int array[size];
    printf("| %5d ", size);

    for (int arrayType = 0; arrayType < 3; arrayType++) {
        initializeArray(array, size, arrayType);
        performHeapSort(array, size);
        printf("| %9d ", comparisonCount + swapCount);
    }

    printf("|\n");
}

int main() {
    srand(time(NULL));

    printf("Heap Construction Complexity Analysis\n");
    printf("+-------+------------+------------+------------+-----------+\n");
    printf("| Size  | Decreasing | Random     | Increasing | Theory    |\n");
    printf("+-------+------------+------------+------------+-----------+\n");


    for (int i = 100; i <= 500; i+=100) {
        testHeapBuilding(i);
    }

    printf("+-------+------------+------------+------------+-----------+\n");

    printf("\nHeap Sort Performance Analysis\n");
    printf("+-------+-----------+-----------+-----------+\n");
    printf("| Size  | Decreasing| Increasing| Random    |\n");
    printf("+-------+-----------+-----------+-----------+\n");

    for (int i = 100; i <= 500; i+=100) {
        testSortingPerformance(i);
    }

    printf("+-------+-----------+-----------+-----------+\n");

    return 0;
}