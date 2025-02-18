n , k= map(int,input().split())
y = list(map(int,input().split()))
cnt = 0
for i in y:
    if i +k <=5:
        cnt +=1
print(cnt//3)

    