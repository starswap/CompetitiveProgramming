T = int(input())
for t in range(T):
    N, K = map(int, input().split())
    a = [*map(int, input().split())]
    ans = 0

    best_mod = 10000
    for item in a:
        best_mod = min(best_mod, (K - (item % K)) % K)
    ans = best_mod

    if K == 4:
        num_evens = 0
        for item in a:
            if item % 2 == 0:
                num_evens += 1

        ans = min(ans, max(0, 2 - num_evens))

    print(ans)