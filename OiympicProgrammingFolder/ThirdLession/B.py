k = int(input())
a = list(map(int, input().split()))
min_n = min(a)
summ = 0
for i in a:
    summ += (i-min_n)
print(summ)