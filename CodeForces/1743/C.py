T = int(input())
for t in range(T):
    N = int(input())
    lids = input() + "0" # Make sure to add the last run
    nums = [*map(int, input().split())] + [0] # This value can be anything to avoid index oob.

    lastZero = 0
    totalRun = 0

    maxSave = 0

    for i,lid in enumerate(lids):
        if lid == '0':
            maxSave += totalRun
            lastZero = nums[i]
            totalRun = 0
        else:
            shiftScore = totalRun + lastZero
            if shiftScore > totalRun + nums[i]:
                maxSave += shiftScore
                lastZero = nums[i]
                totalRun = 0
            else:
                totalRun += nums[i]
    
    print(maxSave)
