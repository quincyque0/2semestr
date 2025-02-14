n = int(input())
command = list(map(int,input().split()))
count1 = command.count(1)
count2 = command.count(2)
count3 = command.count(3)
cm = [0,0,0]
c1=[]
c2=[]
c3=[]
for i in range(len(command)):
    if(command[i]==1):
        c1.append(i)
    
    if(command[i]==2):
        c2.append(i)
    if(command[i]==3):
        c3.append(i)
        
m = min(count1,count2,count3)
print(m)
ind =0
for i in range(m):
    
    print(c1[ind]+1,c2[ind]+1,c3[ind]+1)
    ind +=1