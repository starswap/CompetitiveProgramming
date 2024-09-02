T = int(input())
for t in range(T):
    x, k = map(int, input().split())

    for i in range(x, 10000000000):
        if (sum(map(int, list(str(i)))) % k == 0):
            print(i)
            break