n = int(input())
nums = [*map(int, input().split())]
nums.sort()
bestPrev = 0
for i, item in enumerate(nums):
    bestPrev = min(item, 1 + bestPrev)
print(bestPrev)
