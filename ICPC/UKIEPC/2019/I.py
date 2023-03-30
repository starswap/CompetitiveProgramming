
L, N = map(int, input().split())

d = N - (1 << (L - 1))
if d < 0:
    print("impossible")
else:
    n = 0
    v = 1 << (L - 1)
    while v >= 1:
        if n > 0:
            print(v + d, end=" ")
            print(*([v] * n))
        else:
            print(v + d)
        
        n += 1
        v >>= 1
        