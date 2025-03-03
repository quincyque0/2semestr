k = int(input())
otvet =['']*k
for i in range(k):
    for j in range(8):
        a = input()
        for z in a:
            if z != '.':
                otvet[i]+=z
for i in range(k):
    print(otvet[i])
    if(i != ''):
        print()
        
        
        


    
    