import sys
from math import ceil

N = int(input())
pairs = [tuple(map(int, input().split())) for n in range(N)]
lhs = set(map(lambda x : x[0], pairs))
rhs = set(map(lambda x : x[1], pairs))


if pairs == [(2, 2)]:
    print("NO")
else:

    ans = []
    for i in range(2, 2 * N + 1, 2):
        if i not in lhs:
            ans = [(i // 2, j) for j in range(1, N + 1)]
            break            
        if i not in rhs:
            ans = [(j, i // 2) for j in range(1, N + 1)]
            break

    if not ans:
        for (l, r) in pairs:
            if l == 2:
                twoMap = r
            elif l == 4:
                fourMap = r

        if (twoMap // 2) <= ceil(N / 2):
            ans = [(1, i) for i in range(twoMap // 2 + 1, N + 1)]
        else:
            ans = [(1, i) for i in range(1, twoMap // 2)]

        if (fourMap // 2) <= ceil(N / 2):
            ans += [(2, i) for i in range(fourMap // 2 + 1, N + 1)]
        else:
            ans += [(2, i) for i in range(1, fourMap // 2)]

    print("YES")
    for row in ans[:N]:
        print(*row)
