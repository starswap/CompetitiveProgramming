def solve(nums):
    pass

T = int(input())
for t in range(T):
    N = int(input())
    nums = [*map(int, input().split())]
    print(solve(nums))
