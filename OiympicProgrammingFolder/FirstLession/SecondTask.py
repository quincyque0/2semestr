participant ,score = map(int, input().split()) 
s = list(map(int,input().split()))

mes = score - 1
Itog = 0

if s[mes] > 0:
    for i in range(mes+1,participant):
        if s[mes] > s[i]:
            print(i)
            break
else:
    for i in range(mes, -1, -1):
        if s[i] > 0:
            print(i+1)
            break
        else:print(0)
        

