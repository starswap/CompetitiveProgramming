def maxWins(m,a):
    acc = 0
    ct = 0
    for item in sorted(a): 
        acc += item
        if acc <= m:
            ct += 1
        else:
            break
    return ct

T = int(input())
for t in range(T):
    n,m  = map(int, input().split())
    a = list(map(int,input().split()))

    ct = maxWins(m, a)
    if ct == n:
        print(1)
    else:
        if (a[ct] <= m):
            ctAssuming = maxWins(m-a[ct],a[:ct] + a[ct+1:]) + 1
            if ctAssuming == ct:
                beaten = ct + 1
            else:
                beaten = ct
        else:
            beaten = ct
    
        print(n - beaten + 1)
