n = int(input())

for _ in range(n):
    b,c,h = map(int,input().split())
    nach = c + h
    if b > nach:
        print(nach * 2 + 1)
    else:
        print(b * 2 - 1)
        