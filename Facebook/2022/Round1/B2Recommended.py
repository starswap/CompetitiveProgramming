
MOD = 1000000007

T = int(input())
for t in range(T):
    N = int(input())
    
    trees = []
    for n in range(N):
        trees.append(tuple(map(int,input().split())))

    sigmaTreeXSquared = sum(map(lambda tree : ((tree[0] % MOD) * (tree[0] % MOD)) % MOD ,trees)) % MOD
    sigmaTreeYSquared = sum(map(lambda tree : ((tree[1] % MOD) * (tree[1] % MOD)) % MOD,trees)) % MOD
    sigmaTreeX = sum(map(lambda tree : tree[0] % MOD,trees)) % MOD
    sigmaTreeY = sum(map(lambda tree : tree[1] % MOD,trees)) % MOD


    Q = int(input())

    #OR precompute all sigma(well**2) and then add that to the sigmaTree Squared (also pre-computed) and the dot product one (which can't be precomputed) 
    sumTotal = 0
    for q in range(Q):
        X,Y = map(int,input().split())
        sumTotal += ((N*(X**2 % MOD) % MOD - (2*X*sigmaTreeX % MOD) + sigmaTreeXSquared) % MOD)
        sumTotal += ((N*(Y**2 % MOD) % MOD - (2*Y*sigmaTreeY % MOD) + sigmaTreeYSquared) % MOD)
        sumTotal %= MOD

    print(f"Case #{t+1}: {sumTotal}")

