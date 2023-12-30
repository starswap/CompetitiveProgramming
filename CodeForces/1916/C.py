T = int(input())

def f(t):
    if t == 1:
        return 1
    elif t == 2 or t == 0:
        return 0
    else:
        return t // 3 + f(t % 3)

for t in range(T):
    N = int(input())
    A = map(int, input().split())
    
    t = 0
    s = 0
    ans = []
    for i, num in enumerate(A):
        t += 1 if num % 2 == 1 else 0
        s += num
        if i == 0:
            ans.append(s)
        else:
            ans.append(s - f(t))
    print(*ans)