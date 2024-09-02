import sys
# sys.setrecursionlimit(1000000)
INF = 1000000000000000
bestIs = {}
def solve(n, maxi, cumsum):
    if cumsum >= 42:
        return INF
    if n == 1:
        return 41 - cumsum
        
    best = INF
    bestI = 0
    for i in range(maxi, 0, -1):
        if n % i == 0:
            cache = 1 + solve(n // i, i, cumsum + i)
            if cache < best:
                best = cache
                bestI = i

    bestIs[(n, maxi, cumsum)] = bestI
    return best # print(bestI)

def get_answer(n, maxi, cumsum):
    if n == 1:
        return [1] * (41 - cumsum)
    else:
        i = bestIs[(n, maxi, cumsum)]
        return [i] + get_answer(n // i, i, cumsum + i)
T = int(input())
for t in range(T):
    P = int(input())
    
    factors = []
    changed = True
    length = solve(P, 41, 0)
    if length >= INF:
        print(f"Case #{t + 1}: -1")
    else:
        answer = get_answer(P, 41, 0)
        print(f"Case #{t + 1}: {length} {' '.join(map(str, answer))}")