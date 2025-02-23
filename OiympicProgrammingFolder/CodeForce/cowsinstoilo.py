def can_place_cows(stalls, n, k, mid):
    last = stalls[0]
    count = 1
    for i in range(1, n):
        if stalls[i] - last >= mid:
            last = stalls[i]
            count += 1
            if count == k:
                return True
    return False

def find_max_min_distance(stalls, n, k):
    stalls.sort()
    left = 0
    right = stalls[-1] - stalls[0]
    result = 0
    while left <= right:
        mid = (left + right) // 2
        if can_place_cows(stalls, n, k, mid):
            result = mid
            left = mid + 1
        else:
            right = mid - 1
    return result

# Чтение входных данных
with open('cows.in', 'r') as file:
    lines = file.readlines()
    n, k = map(int, lines[0].split())
    stalls = list(map(int, lines[1].split()))

# Нахождение максимального минимального расстояния
max_min_distance = find_max_min_distance(stalls, n, k)

# Запись результата в выходной файл
with open('cows.out', 'w') as file:
    file.write(str(max_min_distance))
