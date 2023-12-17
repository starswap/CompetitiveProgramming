from collections import Counter
T = int(input())
for t in range(T):
    N = int(input())
    c = Counter()
    for n in range(N - 1):
        l, r = map(int, input().split())
        c[l] += 1
        c[r] += 1
    
    cnt = 0
    for item in c:
        if c[item] == 1:
            cnt += 1
    print((cnt + 1)//2)
