k = int(input())
a = input()
summ = 0
current = 1
for i in range(len(a)//2):
    if a[-current] == '0' and a[current-1] == '1' or a[-current] == '1' and a[current-1] == '0':
        summ+=1
        current+=1
print(len(a) - (summ*2))
    

