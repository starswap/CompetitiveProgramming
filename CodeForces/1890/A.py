from collections import Counter
T = int(input())
for t in range(T):
    N = int(input())
    nums = map(int, input().split())
    cnt = Counter(nums)
    if len(cnt) == 1:
        print("Yes")
    elif len(cnt) == 2:
        nums = [cnt[c] for c in cnt]
        if abs(nums[0] - nums[1]) <= 1:
            print("Yes")
        else:
            print("No")
    else:
        print("No")