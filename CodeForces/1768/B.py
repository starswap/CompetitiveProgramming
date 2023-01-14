from math import ceil
T = int(input())
for t in range(T):
    n,k = map(int, input().split())
    ns = map(int, input().split())

    x = 1
    for item in ns:
        if item == x:
            x += 1
    x -= 1
    print(ceil((n-x)/k))