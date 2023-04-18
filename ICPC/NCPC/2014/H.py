def is_cyclic_perm_KMP(A, B):
    STRING = A + A
    PATTERN = B

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
        if STRING[s] != PATTERN[p]:
            p = lps[p-1]
            if p == 0:
                s += 1    
        else:
            s += 1
            p += 1
        
        if p == len(lps):
            return True
        
    return False

N = int(input())
clock1 = sorted([*map(int, input().split())])
clock2 = sorted([*map(int, input().split())])
diffs1 = [clock1[i] - clock1[i - 1] for i in range(1, N)] + [(360000 + clock1[0] - clock1[-1])]
diffs2 = [clock2[i] - clock2[i - 1] for i in range(1, N)] + [(360000 + clock2[0] - clock2[-1])]

print("possible" if is_cyclic_perm_KMP(diffs1, diffs2) else "impossible")
