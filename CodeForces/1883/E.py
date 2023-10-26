import math
T = int(input())
for t in range(T):
    N = int(input())
    nums = [*map(int, input().split())]
    ans = 0
    divisor = 0
    
    total = 0

    for i in range(1, N):
        curr = nums[i]
        this = 0
        if curr > nums[i - 1]:
            while curr > nums[i - 1]:
                this -= 1
                curr /= 2
            if curr < nums[i - 1]:
                this += 1
                curr *= 2
        else:                
            while curr < nums[i - 1]:
                this += 1
                curr *= 2
        # print(this)
        total += this
        total = max(0, total)
        ans += total

    print(ans)