T = int(input())
for t in range(T):
    N = int(input())
    A = [*sorted(map(int, input().split()))][::-1]
    score = 0
    for i in range(N):
        score += A[2 * i + 1]
    print(score)