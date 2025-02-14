n = int(input())
k = int(input())
for i in range(k):
    a = list(map(int,input().split()))

    odd =0
    even = 0
    for i in range(n):
        if i % 2 != 0 and a[i]% 2 == 0:
            even += 1
        if i % 2 ==0 and a[i] %2  != 0:
            odd
    if odd == even:
        print(odd)
    else:print(-1)
        