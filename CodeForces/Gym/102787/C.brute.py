N, Q = map(int, input().split())
lets = [*map(int, input())]
for q in range(Q):
    T, L, R = map(int, input().split())
    L -= 1
    R -= 1
    if T == 1:
        for i in range(L, R + 1):
            lets[i] = 1 - lets[i]
    elif T == 2:
        lets[L:R + 1] = lets[L:R+1][::-1]
    else:
        lets[L:R + 1] = sorted(lets[L : R + 1])
    
    amnt = 1
    best = 1
    for i in range(1, N):
        if (lets[i] == lets[i - 1]):
            amnt += 1
        else:
            amnt = 1
        best = max(best, amnt)
    print(best)
