T = int(input())

def tryK(impossible, oldK, A_, B_):
    k = oldK
    while k > N: 
        A_, B_ = B_, A_
        k -= N
    B_new = B_[k:] + A_[:k]
    A_new = A_[k:] + B_[:k]

    impossible = impossible or A_new[::-1] != B_new

    for i in range(N):
        if A_new[i] == B_new[i] and not( N % 2 == 1 and i == N // 2):
            impossible = True
        elif A_new[i] < B_new[i] and i >= (N + 1)//2:
            impossible = True
        elif A_new[i] > B_new[i] and i < (N + 1)//2:
            impossible = True
    if impossible:
        return -1
    else:
        return oldK

for t in range(T):
    N = int(input())
    A = [*map(int, input().split())]
    B = [*map(int, input().split())]
    Agt = [A[i] > B[i] for i in range(N)]

    switches = 0
    for i in range(N - 1):
        if Agt[i + 1] != Agt[i]:
            switches += 1
    
    impossible = switches >= 2
    falseCount = Agt.count(False)

    if Agt[0] == False:
        if falseCount >= N // 2:
            k = falseCount - N // 2
        else:
            k = falseCount + N + N // 2
    else:
        k = (N - falseCount) + N // 2
    best = 1000000000
    # print(k)
    for j in range(k - 2, k + 2):
        if j < 0:
            j = 2 * N + j
        j %= 2 * N
        # if (j >= 2 * N):
        #     print(j)

        # print(j)
        if tryK(impossible, j, A, B) != -1:
            best = min(best, tryK(impossible, j, A, B))
    if best == 1000000000:
        best = -1
    print(f"Case #{t + 1}: {-1 if impossible else best}")
    