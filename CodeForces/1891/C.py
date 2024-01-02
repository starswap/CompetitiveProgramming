from collections import deque

def solve(ms):
    ms.sort()
    q = deque(ms)
    x = 0
    steps = 0

    while len(q) > 1:
        time_to_combo = q[-1] - x
        delta = min(time_to_combo, q[0])
        q[0] -= delta
        x += delta
        steps += delta
        if q[0] == 0:
            q.popleft()
        if x == q[-1]: # execute combo
            x = 0
            q.pop()
            steps += 1

    if (len(q) > 0): # one left
        targ = (x + q[-1]) // 2
        amt_needed = targ - x

        # build combo
        steps += amt_needed
        q[-1] -= amt_needed
        x += amt_needed

        # use combo
        if x != 0:
            x = 0
            steps += 1
        
        # do any remaining (at most 1)
        q[-1] -= targ
        steps += q[-1]
    return steps

T = int(input())
for i in range(T):
    N = int(input())
    ms = [*map(int, input().split())]
    print(solve(ms))
