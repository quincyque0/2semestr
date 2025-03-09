import math

n = int(input())

for _ in range(n):
    l, r = map(int, input().split())
    if l > r:
        print(0)
        continue
    discriminant = 1 + 8 * (r - l)
    k = (1 + math.isqrt(discriminant)) // 2
    print(k)
        