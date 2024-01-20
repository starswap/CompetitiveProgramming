T = int(input())

def process_dividers(A):
    Dd = [0 for i in range(N)]
    Dn = [0 for i in range(N)]
    for i in range(1, N - 1):
        if (A[i] - A[i - 1]) < (A[i + 1] - A[i]):
            Dd[i + 1] += A[i + 1] - A[i]
            Dn[i + 1] += 1

    Ds = [0 for i in range(N)]
    Dns = [0 for i in range(N)]
    for i in range(1, N):
        Ds[i] = Ds[i - 1] + Dd[i]
        Dns[i] = Dns[i - 1] + Dn[i]
    return Ds, Dns

for t in range(T):
    N = int(input())
    A = [*map(int, input().split())]
    M = int(input())

    fds, fdns = process_dividers(A)
    bds, bdns = process_dividers([*map(lambda x : x * -1, A[::-1])])
    bdns = bdns[::-1]
    bds = bds[::-1]

    for m in range(M):
        L, R = map(int, input().split())
        L -= 1
        R -= 1
        if R > L:
            dividers = fdns[R] - fdns[L]
            divsum = fds[R] - fds[L]
        else:
            dividers = bdns[R] - bdns[L]
            divsum = bds[R] - bds[L]
        print((abs(R - L) - dividers) + divsum)
