T = int(input())
for t in range(T):
    N = int(input())
    i = 1
    while i <= N:
        i *= 2
    i //= 2
    print(i)