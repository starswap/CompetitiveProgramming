from functools import lru_cache
T = int(input())

@lru_cache(maxsize=100*100)
def f(s, i, j):
    if j < i:
        return 0
    ans = ((j - i + 1) + 2) // 3
    for k in range(i, j + 1):
        if s[k] == "0":
            ans = min(ans, f(s, i, k - 1) + f(s, k + 1, j))
    return ans

for t in range(T):
    N = int(input())
    s = input()
    ans = 0

    done = 0
    for i in range(N):
        for j in range(i, N):
            ans += f(s, i, j)
            done += 1
    print(ans)