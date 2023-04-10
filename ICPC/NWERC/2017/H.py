def getScore(a,b,c):
    return a*a + b*b + c*c + 7 * min(a, b, c)

def tryScore(a,b,c,d):
    if d == 0:
        return getScore(a,b,c)
    else:
        return max(
            tryScore(a + 1, b, c, d - 1),
            tryScore(a, b + 1, c, d - 1),
            tryScore(a, b, c + 1, d - 1)
        )

N = int(input())
for i in range(N):
    a,b,c,d = map(int, input().split())
    
    if d > 3:
        if a >= max(b,c):
            a += d
        if b >= max(a,c):
            b += d
        if c >= max(a,b):
            c += d
        score = getScore(a,b,c)
    else:
        score = tryScore(a,b,c,d)
    print(score)
