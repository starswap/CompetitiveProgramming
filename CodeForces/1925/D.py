T = int(input())
MOD = 1000000007
def inv(x):
    return pow(x, -1, MOD)

for t in range(T):
    N, M, K = map(int, input().split())
    total = 0 
    for i in range(M):
        A, B, F = map(int, input().split())
        total += F
    G = (N * (N - 1)) // 2

    ans = 0
    for k in range(K):
        ans += ((total + ((k * M % MOD) * inv(G) % MOD)) % MOD) * inv(G) % MOD
        ans %= MOD
    print(ans)