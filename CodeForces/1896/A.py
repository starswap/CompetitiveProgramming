T = int(input())
for t in range(T):
    N = int(input())
    nums = [*map(int, input().split())]
    if nums[0] == min(*nums):
        print("YES")
    else:
        print("NO")