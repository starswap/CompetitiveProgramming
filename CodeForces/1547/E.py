Q = int(input())
INF = 100000000000000000
for q in range(Q):
    input()
    n,k = map(int, input().split())
    posnsIn = list(map(lambda a : int(a) - 1, input().split()))
    tempsIn = list(map(lambda a : int(a), input().split()))
    allTemps = [INF for i in range(n)]
    for i,item in enumerate(posnsIn):
        allTemps[item] = tempsIn[i]

    bestLeft = [INF for i in range(n)]
    bestI = 0
    for i in range(0,n):
        # print(condPtr)
        # print(temps)
        tempHere = allTemps[bestI] + (i - bestI)
        if allTemps[i] != -1 and allTemps[i] < tempHere:
            bestI = i
            bestLeft[i] = allTemps[i]
        else:
            bestLeft[i] = tempHere

    bestRight = [INF for i in range(n)]
    bestI = n-1
    for i in range(n-1,-1,-1):
        tempHere = allTemps[bestI] + (bestI - i)
        
        if allTemps[i] != -1 and allTemps[i] < tempHere:
            bestI = i
            bestRight[i] = allTemps[i]
        else:
            bestRight[i] = tempHere
    # print(bestLeft)
    # print(bestRight)
    # print(temps)
    print(" ".join(map(str,map(lambda t : min(t[0],t[1]),zip(bestLeft, bestRight)))))
        