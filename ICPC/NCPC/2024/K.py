N,X = list(map(int, input().split()))
occur = (N//2 - X//2)//X * 2 + 1
if N % X == 0:
    print(0)
else:
    print(N - X * occur)
