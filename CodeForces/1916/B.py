import math
T = int(input())
for t in range(T):
    A, B = map(int, input().split())
    ans = math.lcm(A, B)
    if ans == B:
        ans *= (B // A)
    print(ans)