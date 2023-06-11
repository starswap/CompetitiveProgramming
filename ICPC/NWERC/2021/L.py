n, i, k = map(int, input().split())

def pm(m, k, n):
    """P(M < m)"""
    return ((m - 1)/n)**k

def pmq(m, k, n):
    """P(M = m)"""
    return pm(m + 1, k, n) - pm(m, k, n)

ans = pm(i, k, n) * i
for a in range(i, n + 1):
    ans += ((a + 1)/2) * (pmq(a, k, n))

print(ans)
