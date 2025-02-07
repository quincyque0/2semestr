n,s = map(int,input().split())
arr = list(input())
for i in range(s):
    j = 0
    while j < n-1:
        if arr[j] == 'B' and arr[j+1] == 'G':
            arr[j], arr[j+1] = arr[j+1], arr[j]
            j+=1
        j+=1
print(*arr,sep='')
print("".join(arr))