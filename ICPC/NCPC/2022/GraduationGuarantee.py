from collections import defaultdict 
def solve(N,K,p):
    p.sort(reverse=True)
    scoresDict = defaultdict(lambda: 0)
    scoresDict[1] = p[0]
    scoresDict[-1] = 1-p[0]
    ans = 0
    if N == 1:
        return p[0]

    for q in range(1,N):
        newDict = defaultdict(lambda: 0)
        for score in range(-q-1,q+2):
            newDict[score] = p[q] * scoresDict[score-1] + (1-p[q]) * scoresDict[score+1]
        
        thisRound = 0
        
        scoresDict = newDict
        for (k,v) in scoresDict.items():
            if k >= K:  
                thisRound += v
        ans = max(ans, thisRound)

    return ans


N, K = map(int,input().split())
p = list(map(float,input().split(" ")))
print(solve(N,K,p))

