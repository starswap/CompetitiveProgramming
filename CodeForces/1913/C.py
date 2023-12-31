from collections import Counter
from copy import deepcopy

def getbits(n):
    bits = []
    for i in range(31):
        if n & (1 << i):
            bits.append(i)
    return bits[::-1]

Q = int(input())
have = Counter()

for t in range(Q):
    op, n = map(int, input().split())

    if op == 1:
        have[n] += 1
    else:
        i = 31
        while n > 0 and i > -1:
            if (have[i]):
                will_use = min(n // (1 << i), have[i])
                n -= (1 << i) * will_use
            i -= 1

        if n == 0:
            print("YES")
        else:
            print("NO")

        # # need = getbits(n)

        # # ok = True
        # # for bit in need:
        # #     removal = 1
        # #     for i in range(bit, -1, -1):
        # #         if have_copy[i] >= removal:
        # #             have_copy[i] -= removal
        # #             break
        # #         else:
        # #             removal *= 2
        # #     else:
        # #         ok = False
        # if ok:
        #     print("YES")
        # else:
        #     print("NO")
