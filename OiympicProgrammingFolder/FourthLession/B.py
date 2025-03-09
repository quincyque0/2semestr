n = int(input())
 
for _ in range(n):
     i = int(input())
     s = input()
     pl = s.count("+")
     mi = s.count("-")
     print(abs(mi-pl))