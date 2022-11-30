import itertools
T = int(input())
for t in range(T):
    n = int(input()) 
    nums = [*sorted(map(int, input().split()))]

    grps = [len([*g]) for (k,g) in itertools.groupby(nums)]
    
    if (len(grps) == 1):
        print(max(1,n//2))
    else:
        # score = 0
        sumSoFar = 0
        # print(grps)
        for grp in grps:
            if (sumSoFar * grp <= ((n-grp-sumSoFar) * grp)):
                sumSoFar += grp
            else:
                break

        print(sumSoFar * (n - sumSoFar))

