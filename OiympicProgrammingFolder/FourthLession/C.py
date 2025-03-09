m = [[1,1,1],
     [1,1,1],
     [1,1,1]]

for _ in range(3):
    i = input().split()
    for j in range(3):
        if int(i[j]) % 2 != 0:
            m[i][j]  = abs(m[i][j] - 1)
            if i > 0:
                m[i - 1][j] = abs(m[i-1][j] - 1)
            if i < 2:
                m[i + 1][j] = abs(m[i+1][j] - 1)
            if i > 0:
                m[i][j-1] = abs(m[i][j-1] - 1)
            if i < 2:
                m[i][j+1] = abs(m[i][j+1] - 1)
    print("".join(m[i]))
            
        