n, m, c = map(int, input().split())

# Brute force using gray code subset enumeration

def LSOne(x):
    return x & -x

def count(it):
    counts = [0 for i in range(c)]
    for item in it:
        counts[item - 1] += 1
    return counts

def ctz(x):
    mask = 1
    cnt = 0
    while not(mask & x):
        cnt += 1
        mask <<= 1
    return cnt

if n == 1:
    nums = map(int, input().split())
    counts = count(nums)
    if (all(map(lambda x : x == counts[0], counts))):
        print(1)
    else:
        print(0)
else:
    row_counts = []
    for row in range(n):
        nums = map(int, input().split())
        counts = count(nums)
        row_counts.append(counts)

    mask = 0
    colour_counts = [0 for i in range(c)]
    cnt = 0
    best = 0
    for i in range(1, 1 << n):
        if all(map(lambda x: x == colour_counts[0], colour_counts)):
            best = max(best, cnt)
        if LSOne(i) & mask:
            cnt -= 1
            for j, count in enumerate(row_counts[ctz(LSOne(i))]):
                colour_counts[j] += count
        else:
            cnt += 1
            for j, count in enumerate(row_counts[ctz(LSOne(i))]):
                colour_counts[j] -= count
        mask ^= LSOne(i)
    if all(map(lambda x: x == colour_counts[0], colour_counts)):
        best = max(best, cnt)

    print(best)


        