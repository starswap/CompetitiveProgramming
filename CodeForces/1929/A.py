T = int(input())
for t in range(T):
    N = int(input())
    A = [*map(int, input().split())]
    mini = min(*A)
    maxi = max(*A)
    print(maxi - mini)