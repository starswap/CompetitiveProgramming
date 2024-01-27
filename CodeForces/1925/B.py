import math
T = int(input())

for t in range(T):
    X, N = map(int,input().split())
    i = 1
    best = 0
    while i * i <= X:
        if X % i == 0 and X // i >= N:
            best = max(best, i)
        if X % i == 0 and i >= N:
            best = max(best, X // i)
        i += 1
    print(best)