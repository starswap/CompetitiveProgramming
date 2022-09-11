#Turn y back on
#Streamline

def solveForOneDimension(trees,WellA,Contrib,dim):
    """a Represents either x or y"""

    sigmaASquared = 0    

    for coords in trees:
        sigmaASquared +=  (WellA[0][0] - coords[dim])**2

    leftSet = [coords[dim] for coords in trees if coords[dim] <= WellA[0][0]]
    rightSet = [coords[dim] for coords in trees if coords[dim] > WellA[0][0]]
    rightSet.sort(reverse=True)

    numLeft = len(leftSet)
    numRight = len(rightSet)

    sigmaALeft = sum(map(lambda a : WellA[0][0] - a, leftSet))
    sigmaARight = sum(map(lambda a : a - WellA[0][0], rightSet))

    Contrib[WellA[0][1]] = sigmaASquared % MOD

    for i,well in enumerate(WellA[1:]): #i  starts at 0, even though we are talking about index 1. So i is the index of the previous well.
        sigmaALeftOld = sigmaALeft
        sigmaARightOld = sigmaARight

        a,q = well
        deltaA = a-WellA[i][0]
        treesMoved = []
        while numRight > 0 and rightSet[-1] <= a:
            swappedSide = rightSet.pop()
            sigmaARight -= (swappedSide-WellA[i][0])
            treesMoved.append(swappedSide)
            numRight -= 1
                
        sigmaARight -= numRight*deltaA
        sigmaALeft += numLeft*deltaA

        for moved in treesMoved:
            sigmaALeft += a-moved
            numLeft += 1
            leftSet.append(moved) #don't necessarily need
        
        qOld = WellA[i][1]
        Contrib[q] = (
            Contrib[qOld] % MOD + # x^2
            2*deltaA*sigmaALeftOld % MOD - # + 2ax
            2*deltaA*sigmaARightOld % MOD + # - 2ax
            (numLeft+numRight)*((deltaA % MOD)*(deltaA % MOD) % MOD) % MOD # + a^2
        ) % MOD

MOD = 1000000007

T = int(input())
for t in range(T):
    N = int(input())
    
    trees = []
    for n in range(N):
        trees.append(tuple(map(int,input().split())))

    Q = int(input())

    XContrib = [0 for i in range(Q)]
    YContrib = [0 for i in range(Q)]

    WellX = []
    WellY = []
    for q in range(Q):
        X,Y = map(int,input().split())
        WellX.append((X,q))
        WellY.append((Y,q))

    WellX.sort()
    WellY.sort()

    solveForOneDimension(trees,WellX,XContrib,0)
    solveForOneDimension(trees,WellY,YContrib,1)

    sumTotal = 0
    for q in range(Q): #We need the sum over all locations, not even the value for each location, so we don't actually need to store the scores for each query. 
        sumTotal += (XContrib[q] % MOD) 
        sumTotal %= MOD
        sumTotal += (YContrib[q] % MOD)
        sumTotal %= MOD

    print(f"Case #{t+1}: {sumTotal}")