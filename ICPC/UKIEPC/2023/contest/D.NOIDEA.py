
n = int(input())

nums = list(map(int, input().split()))


nums.sort(reverse=True)
tot = 0
done = 0
for i in range(0, len(nums), 2):
    tot += nums[i+1]
    done += 1
    if done == len(nums)//3: