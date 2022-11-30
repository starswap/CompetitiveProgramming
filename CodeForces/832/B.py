from math import ceil
T = int(input())
for t in range(T):
    n = int(input())
    B = 1
    N = 3*n
    
    print(max(1,ceil(n/2)))
    while N > B:
        print(str(B) + " " + str(N))
        N -= 3
        B += 3