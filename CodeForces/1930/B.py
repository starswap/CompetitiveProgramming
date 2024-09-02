T = int(input())
for t in range(T):
    N = int(input())
    perm = []
    for i in range(N // 2):
        perm.append(i + 1)
        perm.append(N - i)
    if N % 2 == 1:
        perm.append(N // 2 + 1)
    print(*perm)