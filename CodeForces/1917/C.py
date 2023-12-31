T = int(input())
for t in range(T):
    N, D = map(int, input().split())
    A = [*map(int, input().split())]
    B = [*map(int, input().split())]
    MAX_N = 8000
    best = 0
    for i in range(min(D, 2 * MAX_N + 5)):
        pre_score = 0
        for j in range(1, N + 1):
            if A[j - 1] == j:
                pre_score += 1
    
        remaining = D - i - 1
        extra_score = remaining // 2

        best = max(best, pre_score + extra_score)

        for j in range(B[i]):
            A[j] += 1
    print(best)