def quick_sort_standard(A):
    if len(A) > 0:
        _quick_sort_standard(A, 0, len(A) - 1)
    print("______")
    print(' '.join(A))

def _quick_sort_standard(A, L, R):
    print(' '.join(str(i) for i in range(L, R + 1)))
    print(' '.join(A[i] if i >= L and i <= R else ' ' for i in range(13)))
    if L >= R:
        return
    i, j = partition(A, L, R)
    if L < j:
        _quick_sort_standard(A, L, j)
    if i < R:
        _quick_sort_standard(A, i, R)

def partition(A, L, R):
    x = A[L]
    print(f"Обведён в круг: {x}({L})")
    i = L
    j = R
    i_positions = []
    j_positions = []
    
    while i < j:
        while i <= R and A[i] < x:
            i += 1
        while j >= L and A[j] > x:
            j -= 1
        
        if i <= R:
            i_positions.append(f"{A[i]}({i})")
        if j >= L:
            j_positions.append(f"{A[j]}({j})")
        
        if i_positions:
            print(f"Верхнее подчёркивание: {' '.join(i_positions)}")
        if j_positions:
            print(f"Нижнее подчёркивание: {' '.join(j_positions)}")
        
        if i <= j:
            print(f"Перестановка {A[i]}({i}) и {A[j]}({j})")
            A[i], A[j] = A[j], A[i]
            i += 1
            j -= 1
            print(' '.join(str(i) for i in range(L, R + 1)))
            print(' '.join(A[i] if i >= L and i <= R else ' ' for i in range(13)))
        else:
            break
    
    if j >= L:
        print(f"Точка под буквой: {A[j]}({j})")
    if i <= R:
        print(f"Точка над буквой: {A[i]}({i})")
    
    return (i, j)

l = list("РУДОМЕТОВДАН")
quick_sort_standard(l)
