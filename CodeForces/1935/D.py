T = int(input())
for t in range(T):
    N, C = map(int, input().split())
    A = [*map(int, input().split())]
    vals = set(A)
    M = A[-1]

    ans = (C - M) * (M - N + 1)
    ans += ((C - M) * (C - M + 1)) // 2
    totalEven = 0
    totalOdd = 0
    for item in A:
        if item % 2 == 0:
            totalEven += 1
        else:
            totalOdd += 1

    # number of pairs with both up to M
    # with an illegal sum
    # for each x value we can add it up to be bigger than that

    illegalSums = 0
    illegalDiffs = 0
    prev = -1
    for i in range(N):
        seen = i
        unseen = N - i - 1
        inThisRange = A[i] - prev # including A[i] 
        illegalSums += inThisRange * (unseen + 1)
        illegalDiffs += (inThisRange - 1) * seen + (seen + 1)
        prev = A[i]

    # print(illegalDiffs)
    # print(illegalSums)
    illegalSums += totalEven
    illegalSums //= 2 
    # illegalDiffs //= 2
     
    # print("---")
    # print(illegalDiffs)

    

    diffsAndSums = (totalEven * (totalEven + 1)) // 2 + (totalOdd * (totalOdd + 1)) // 2 
    pairsToMax = (M * (M + 1)) // 2 + M + 1
    # print(pairsToMax)
    # print(illegalSums)
    # print(illegalDiffs)
    ans += pairsToMax - illegalSums - illegalDiffs + diffsAndSums
    print(ans)
