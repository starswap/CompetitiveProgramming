from dataclasses import dataclass
from functools import lru_cache
import sys
sys.setrecursionlimit(10000000)

@dataclass
class Cafe:
    open: int
    close: int
    wifi: int

D = int(input())
N = int(input())

cafes = [Cafe(*map(int, input().split())) for i in range(N)]
AM = [[*map(int, input().split())] for i in range(N)]

for k in range(N):
    for i in range(N):
        for j in range(N):
            AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j])

@lru_cache(maxsize=None)
def solve(time, cafe, data_left):
    if time > end:
        return 100000000000
    if time >= cafes[cafe].open and time < cafes[cafe].close:
        data_left -= cafes[cafe].wifi
        if data_left <= 0:
            return time + 1
    ans = solve(time + 1, cafe, data_left)
    for i in range(N):
        ans = min(ans, solve(time + 1 + AM[cafe][i], i, data_left))
    return ans

end = max(map(lambda cafe: cafe.close, cafes))
ans = 100000000000
for i in range(N):
    ans = min(ans, solve(0, i, D))

if ans > 86400:
    print("impossible")
else:
    print(ans)
