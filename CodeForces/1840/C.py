T = int(input())
for t in range(T):
    n, k, q = map(int, input().split())
    temps = list(map(int, input().split()))
    runs = []
    i = 0
    start = -1
    while i < n:
        if (start == -1):
            if (temps[i] <= q):
                start = i
        else:
            if (temps[i] > q):
                length = (i - start)
                if length >= k:
                    runs.append(length)
                start = -1
        i += 1
    length = (i - start)
    if length >= k and start != -1:
        runs.append(length)

#    print(runs)
    ans = 0
    for run in runs:
        ans += (run - k + 1) * (run + 1)
        ans += (k * (k - 1))/2 - (run * (run + 1) / 2)

    print(int(ans))


