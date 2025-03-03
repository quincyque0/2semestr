m = []
for i in range(10):
    s = input()
    m.append(s)
    
for i in range(10):
    ind = m[i].find('x')
    if ind != -1:
        print(min(min(i+1,ind+1),min(10-i,10 - ind)))