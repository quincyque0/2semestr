def merge_sort_visualized(arr):
    """
    Реализует сортировку слиянием с визуализацией этапов слияния.
    """

    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]

    print(f"Разделение: {arr} -> {left_half}, {right_half}")

    left_half = merge_sort_visualized(left_half)
    right_half = merge_sort_visualized(right_half)

    return merge_visualized(left_half, right_half, arr)


def merge_visualized(left, right, original_arr):
    """
    Слияние двух отсортированных массивов с визуализацией.
    """
    merged = []
    i = 0
    j = 0

    print(f"Слияние: left={left}, right={right}")

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            print(f"  Выбрано {left[i]} из left.  merged = {merged}")
            i += 1
        else:
            merged.append(right[j])
            print(f"  Выбрано {right[j]} из right.  merged = {merged}")
            j += 1

    # Добавление оставшихся элементов из left
    while i < len(left):
        merged.append(left[i])
        print(f"  Остаток из left: {left[i]}. merged = {merged}")
        i += 1

    # Добавление оставшихся элементов из right
    while j < len(right):
        merged.append(right[j])
        print(f"  Остаток из right: {right[j]}. merged = {merged}")
        j += 1

    print(f"Результат слияния: {merged}")
    return merged


# Пример использования
example_array = [12, 11, 13, 5, 6, 7]
print("Исходный массив:", example_array)
sorted_array = merge_sort_visualized(example_array)
print("Отсортированный массив:", sorted_array)
