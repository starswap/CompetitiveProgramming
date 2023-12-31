T = int(input())
for t in range(T):
    N = int(input())
    st = input()

    ans = 0
    prev = set([])
    for i in range(N):
        if st[i] not in prev:
            ans += (N - i)
        prev.add(st[i])
    print(ans)