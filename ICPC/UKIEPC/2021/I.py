import math
p = int(input())
reqs = [*map(int, input().split())]
solves = [*map(int, input().split())]
pairs = sorted(filter(lambda x : x[0] != -1, zip(solves, reqs)))

total_time = 0
best = 0
for (solve, req) in pairs:
    total_time += req
    min_n = total_time / solve
    best = max(best, min_n)

EPS = 1e-11
if abs(round(best) - best) < EPS:
    print(round(best))
else:
    print(math.ceil(best))