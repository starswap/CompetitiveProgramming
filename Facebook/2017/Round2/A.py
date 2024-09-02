from math import ceil

T = int(input())
for t in range(T):
    N,M,K = map(int, input().split())
    if min(N,M) > K and max(N,M) > 2*K + 2:
        if N == M:
            
        print(ceil((min(M,N)-1)/K)+1)
        
    else:
        print(-1)
