from math import sqrt, floor

T = int(input())
EPS = 0.000000001

def getFactPairs(n):
    sq = floor(sqrt(n))
    facts = []
    for i in range(1,sq+1):
        if (abs(n/i - n//i) < EPS):
            facts.append((i,n//i))
    return facts


for t in range(T):
    G = int(input())
    possKs = set()
    for (L,H) in getFactPairs(2*G):
        # print(L,H)
        n = (H + L - 1) / 2
        K = H - n
        # print(K)
        if (abs(K - round(K)) < EPS):
            possKs.add(K)

    print(f"Case #{t+1}: {len(possKs)}")


