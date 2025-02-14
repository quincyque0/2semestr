n = int(input())

a = input()

c1 = a.count('1')
c2 = a.count('2')

if (c1 + 2 * c2) % 2 !=0:
    print("No")
    exit()
else:
    f = (c1 + 2 * c2) //2 
    if f % 2 ==0:
        print('Yes')
    else:
        if c1 >=1:
            print('Yes')
        else:print('No')

