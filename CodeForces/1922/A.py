T = int(input())
for t in range(T):
    N = int(input())
    A = input()
    B = input()
    C = input()
    ok = False
    for i in range(N):
        ok |= (A[i] == B[i] and B[i] != C[i]) or (A[i] != B[i] and C[i] != B[i] and C[i] != A[i])
    print("YES" if ok else "NO")