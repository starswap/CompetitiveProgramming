T = int(input())
for t in range(T):
    N = int(input())
    A = [*map(int, input().split())]
    As = sorted([*map(lambda x, y: x + y, A, range(1, N + 1))], reverse = True)
    
    for i in range(1, N):
        if As[i] >= As[i - 1]:
            As[i] = As[i-1]  - 1
    print(*As)

    # remove the one with the highest minimum among those that can make what you want to make.