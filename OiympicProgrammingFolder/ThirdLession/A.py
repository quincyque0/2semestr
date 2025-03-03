k = int(input())
a = list(map(int, input().split()))
max_p = 1
# for i in range(k):
#     copy_a = a[:]
#     copy_a[i] += 1
#     prod = 1
#     for j in copy_a:
#         prod *= j
#     max_p = max(max_p, prod)
min_n = a.index(min(a))
a[min_n] += 1
for i in a:
    max_p *=i
print(max_p)    
        