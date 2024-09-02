from math import ceil

EPS = 0.0000001

def fact(n):
    fs = []
    i = 1
    while i * i <= n:
        if abs((round(n / i)) - n/i) < EPS:
            fs.append(i)
            fs.append(round(n/i))
        i += 1
    return fs


T = int(input())
for t in range(T):
    n = int(input())
    a = [*map(int, input().split())]
    b = [*map(int, input().split())]
    kFails = set()
    strictMin = 0
    
    for i in range(n):
        strictMin = max(strictMin, a[i] - b[i]) 
        if (b[i] < a[i]):
            for f in fact(b[i]):
                kFails.add(f)

    theMin = round(strictMin) + 1
    
    poss = set(range(theMin, n+1)).difference(kFails)
    print(len(poss))
    print(" ".join(map(str,poss)))

# 0 < a <= k
# 0 < b

# a/k -1 <= b/k
# a - k <= b
# a - b <= k
# k < a <= 2k
# a/k -1  <= 0 < b/k

# 5/4 - 1 <= 1 < 2/4

# nk < b < a 