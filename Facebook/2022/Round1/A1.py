import sys

def isCyclicPerm(A,B):
    b = B.index(A[0])
    a = 0
    while a < len(A)-1:
        a += 1
        b += 1
        b %= len(B)
        if (A[a] != B[b]):
            return False
    return True


TCs = int(input())
for t in range(1,TCs+1):
    N,K = map(int,input().split())
    A = list(map(int,input().split()))
    B = list(map(int,input().split()))
    
    CP = isCyclicPerm(A,B)
    
    doable = True
    if K == 0 and A != B:
        doable = False
    elif K == 1 and A == B: #May no longer be true in A2.
        doable = False
    elif N == 2 and CP:
        if A == B:
            doable = (K % 2) == 0
        else:
            doable = (K % 2) != 0
    else:
        doable = CP

    print(f"Case #{t}: {'YES' if doable else 'NO'}")
    sys.stdout.flush()
