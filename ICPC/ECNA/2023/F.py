from math import log2

n = int(input())
nums = list(map(int, input().split()))
nums = [int(log2(x)) for x in nums]

for step in range(len(nums)):
    merged = False
    if len(nums) == 1:
        print(pow(2, nums[0]))
        break
    stk = [nums[0]]
    for j in range(1, len(nums)):
        stk.append(nums[j])
        while len(stk) > 1 and stk[-1] == stk[-2]:
            stk.pop(-1)
            r = stk.pop(-1)
            stk.append(r+1)
            merged = True
    
    if not merged:
        ### Apply our special trick
        low = min(stk)
        occs = []
        for i in range(len(stk)):
            if stk[i] == low:
                occs.append(i)
                if len(occs) == 2:
                    break
        if len(occs) == 1:
            # Just remove the smallest one
            stk = stk[:occs[0]] + stk[occs[0]+1:]
        else:
            ### Need to remove both
            stk = [stk[j] for j in range(len(stk)) if j not in occs]
    nums = stk
