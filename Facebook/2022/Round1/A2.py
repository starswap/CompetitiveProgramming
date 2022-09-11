#TO ADD TO CP LIB.

import sys

def isCyclicPerm_KMP(A,B):
    STRING = A+A
    PATTERN = B
    
    lps = [0 for i in range(len(B))]
    i = 0
    j = 1
    while j < len(lps): # O(M)
        if PATTERN[i] != PATTERN[j]:
            j += 1
            if i > 0:
                i = lps[i-1]
        else:
            lps[j] = i+1
            i += 1
            j += 1

    s = 0
    p = 0
    while s < len(STRING):
        if STRING[s] != PATTERN[p] and p > 0:
            p = lps[p-1]
        else:
            s += 1
            p += 1
        
        if p == len(lps):
            return True
        
    return False


TCs = int(input())
for t in range(1,TCs+1):
    N,K = map(int,input().split())
    A = list(map(int,input().split()))
    B = list(map(int,input().split()))
    
    CP = isCyclicPerm_KMP(A,B)
    
    doable = True
    if K == 0 and A != B:
        doable = False
    elif K == 1 and A == B: #May no longer be true in A2.
        if (N % 2 == 0 and A[:N//2] == A[N//2:]):
            doable = True
        else:
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
