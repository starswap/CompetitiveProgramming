T = int(input())
for t in range(T):
    m,s = map(int,input().split())
    vals = set(map(int,input().split()))

    maxx = max(vals)
    total = sum([i for i in range(maxx) if not(i in vals)])

    i = 1
    while total < s:
        total += maxx + i
        i += 1 

    if total == s:
        print("YES")
    else:
        print("NO")
