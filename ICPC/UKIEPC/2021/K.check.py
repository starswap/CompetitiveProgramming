import math
n = int(input())
assert(n <= 500)
assert(n >= 2)

points = []
for i in range(n):
    x,y = map(float,(input().split()))
    points.append((x, y))

x, y = points[0]
points = points[1:]

total_dist = 0
for (nx, ny) in points:
    total_dist += math.sqrt((nx - x) * (nx - x) + (ny - y) * (ny - y))
    x = nx
    y = ny

print(total_dist)