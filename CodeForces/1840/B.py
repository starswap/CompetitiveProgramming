T = int(input())
for t in range(T):
    n, k = map(int, input().split())
    if (k > n + 1 or k > 40): # avoid massive comp
        print(n + 1)
    else:
        print(min(n + 1, 1 << k))

