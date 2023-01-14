import itertools

T = int(input())
for t in range(T):
    n = int(input())
    nums = list(map(int, input().split()))

    ps = list(itertools.accumulate(nums))

    maxi = max(ps)
    mini = min(ps)

    print(abs(max(maxi, 0)) + abs(min(mini, 0)))

