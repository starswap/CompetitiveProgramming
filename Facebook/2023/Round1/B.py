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

dp = [[[-1 for i in range(42) ] for j in range(42)] for i in range(42)]
def do_DP(i, curr_number, amnt_left_without):
    print(curr_number)
    print(amnt_left_without)
    if i >= len(factors):
        if amnt_left_without - curr_number == 0:
            return 1
        else:
            return INF
    elif curr_number > 41:
        return INF
    elif curr_number != 0 and dp[i][curr_number][amnt_left_without] != -1:
        return dp[i][curr_number][amnt_left_without]
    else:
        if curr_number == 0:
            ans = do_DP(i + 1,factors[i], amnt_left_without - curr_number)
        else:
            ans = min(do_DP(i + 1,factors[i], amnt_left_without - curr_number) + 1,
                      do_DP(i + 1,curr_number * factors[i], amnt_left_without))
        dp[i][curr_number][amnt_left_without] = ans
        return ans

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