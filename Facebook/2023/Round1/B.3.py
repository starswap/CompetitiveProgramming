import itertools
def findsubsets(S,m):
    return itertools.combinations(S, m)
INF = 100000000000
primes = []
def is_prime(x):
    for p in primes:
        if x % p == 0:
            return False
    return True
primes = [2]
for i in range(3, 42):
    if is_prime(i):
        primes.append(i)

T = int(input())
for t in range(T):
    P = int(input())
    
    factors = []
    changed = True
    while P > 1 and changed:
        changed = False
        for prime in primes:
            if P % prime == 0:
                factors.append(prime)
                P /= prime
                changed = True
    if not(changed):
        ans = -1
    else:
        ans = do_DP(0, 0, 41)
    
    print(f"Case #{t + 1}: {ans}")