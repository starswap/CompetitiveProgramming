T = int(input())
for t in range(T):
    N = int(input())
    nums = [*map(int, input().split())][::-1]
    lowest_so_far = 10000000000000

    cnt = 0
    for i in nums:
        if i > lowest_so_far:
            divs = (i // lowest_so_far) + (1 if not i % lowest_so_far == 0 else 0)
            cnt += divs - 1
            i //= divs
        if i != 0:
            lowest_so_far = min(lowest_so_far, i)
    print(cnt)
        