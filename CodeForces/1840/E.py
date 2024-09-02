from collections import deque

T = int(input())
for t in range(T):
    s1 = list(input())
    s2 = list(input())
    s, Q = map(int, input().split())
    count = 0
    queries = []
    unblocks = deque([])
    for q in range(Q):
        while len(unblocks) > 0 and unblocks[0][0] == q:
            unblocks.popleft()

        query = input()

