N, K = map(int, input().split())
dp = [0]*(N + 1)
dp[0] = 1

for t in range(K):
    dpNew = [0]*(N+1)
    dpNew[0] = 0.5 * dp[0]
    for n in range(1,N-1):
        dpNew[n] = 0.5 * dp[n - 1] + 0.5 * dp[n]
    
    if (N != 1):
        dpNew[N - 1] = 0.5 * dp[N] + 0.5 * dp[N - 2] + 0.5 * dp[N - 1]
    else:
        dpNew[N - 1] += 0.5*dp[1]
    dpNew[N] = 0.5 * dp[N] + 0.5 * dp[N - 1]
    dp = dpNew

ans = 0
for h in range(N+1):
    ans += h * dp[h]
print(round(ans,8))
