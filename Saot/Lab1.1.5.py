import random
import time
import matplotlib.pyplot as plt

def select_sort(arr):
    comparisons = 0
    swaps = 0
    n = len(arr)

    for i in range(n - 1):
        min_idx = i
        for j in range(i + 1, n):
            comparisons += 1
            if arr[j] < arr[min_idx]:
                min_idx = j

        if min_idx != i:
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
            swaps += 1

    return comparisons, swaps

def fill_random(n):
    return [random.randint(0, 1000) for _ in range(n)]

def main():
    max_n = 200
    n_values = []
    mf_cf_values = []

    for n in range(10, max_n + 1, 10):
        arr = fill_random(n)
        comparisons, swaps = select_sort(arr)
        mf_cf = swaps + comparisons

        n_values.append(n)
        mf_cf_values.append(mf_cf)

    # Построение графика
    plt.plot(n_values, mf_cf_values, marker='o', linestyle='-', label='Mf+Cf')
    plt.xlabel('n (Размер массива)')
    plt.ylabel('Mf+Cf')
    plt.title('Зависимость Mf+Cf от размера массива для SelectSort')
    plt.grid(True)
    plt.legend()
    plt.show()


main()