import math
line = input().split()
N = int(line[0])
g = float(line[1])

slopes = [[*map(int, input().split())] for i in range(N)]
for start in range(N):
    speed = 0
    for curr in range(start, N):
        D, theta = slopes[curr]
        speed = math.sqrt(speed * speed + 2 * (math.cos(theta / 180 * math.pi) * g) * D)
    print(speed)