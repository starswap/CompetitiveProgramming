import sys

def KMP(STRING,PATTERN):   
    lps = [0 for i in range(len(PATTERN))]
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
    
    CP = KMP(A+A,B)
    
    doable = True
    if K == 0 and A != B:
        doable = False
    elif K == 1 and A == B: #May no longer be true in A2.
        doable = KMP((A+A)[1:-1],B)
    elif N == 2 and CP:
        if (A[0] == A[1] and A[1] == B[0] and B[0] == B[1]):
            doable = True
        elif A == B:
            doable = (K % 2) == 0
        else:
            doable = (K % 2) != 0
    else:
        doable = CP

    print(f"Case #{t}: {'YES' if doable else 'NO'}")
    sys.stdout.flush()
