n = int(input())

x = 0

for i in range(n):
    com = input()
    if "++" in com:
        x+=1
    else:
        x-=1
print(x)