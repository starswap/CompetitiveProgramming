T = int(input())
for t in range(T):
    n,x = map(int, input().split())
    perm = [x]*n
    fail = (x == 1) or (x > n)
    lastForced = x
    for i in range(1,n):
        val = i + 1
        if val >= x and lastForced % val == 0:
            perm[i] =  val * (lastForced/val+1)
            lastForced = val * (lastForced/val+1)
        else:  
            perm[i] = val
        
        if (perm[i] > n or perm[i] == 1) and i != n-1:
            fail = True
            break
    if fail:
        print(-1)
    else:
        perm[-1] = 1
        print(' '.join(map(lambda x : str(int(x)),perm)))
        
