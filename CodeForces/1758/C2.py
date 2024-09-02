T = int(input())
for t in range(T):
    n,x = map(int, input().split())
    if (x == 1) or (n % x != 0) or (2*x > n and n != x):
        print(-1)
    else:
        vals = [x] * n
        currentTimesX = 2*x
        for i in range(1,n):
            val = i+1
            if val == n/2:
                vals[i] = val if x == n else n
            elif val % x == 0:
                vals[i] = int((val / x + 1)* x)
            else:
                vals[i] = val 
                
        vals[-1] = 1
        print(" ".join(map(str,vals)))
        
