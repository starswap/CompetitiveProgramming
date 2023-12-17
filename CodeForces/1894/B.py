from collections import Counter
T = int(input())
for t in range(T):
    N = int(input())
    nums = list(map(int , input().split()))

    pairs = 0
    cnt = Counter(nums)
    pairsVals = []
    for i in cnt:
        if cnt[i] >= 2:
            pairs += 1
            if pairs <= 2:
                pairsVals.append(i)
    if pairs < 2:
        print("-1")
    elif pairs >= 2:
        arr = []
        jjs = [1, 2]
        # print(pairsVals)
        for i in range(N):
            if nums[i] == pairsVals[0]:
                arr.append(jjs[0])
                cnt[nums[i]] -= 1
                if cnt[nums[i]] == 1:
                    jjs[0] += 1
            elif nums[i] == pairsVals[1]:
                arr.append(jjs[1])
                cnt[nums[i]] -= 1
                if cnt[nums[i]] == 1:
                    jjs[1] += 1
            else:
                arr.append(1)        
        print(" ".join(map(str, arr)))
