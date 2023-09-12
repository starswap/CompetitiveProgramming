s = 0.05
n = int(input())

circles = []
for i in range(n):
    circles.append([*map(int, input().split())])

ans = 0
x = -10

while x < 20:
    y = -10
    while y < 20:
        for (cx, cy, r) in circles:
            if (x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r:
                ans += s * s
                break
        y += s
    x += s

print(ans)
