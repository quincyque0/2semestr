import math
k = int(input)
for i in range(k):
    n = int(input())
    a = list(map(int,input.split()))
    
    s = sum(a)
    if math.sqrt(s) % 1 == 0:
        print("Yes")
    else:
        print('No')
