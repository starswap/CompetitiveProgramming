from collections import deque
n, w = map(int, input().split())
ws = sorted([*map(int, input().split())])

ss = deque(ws)
needed = 0
while len(ss) >= 1:
    if (ss[0] + ss[-1] <= w):
        ss.popleft()
        if len(ss) >= 1:
            ss.pop()
    else:
        ss.pop()
    needed += 1

print(needed)
