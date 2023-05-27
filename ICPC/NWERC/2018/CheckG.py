ops = input()
curr = tuple(map(int, input().split()))
N = int(input())
nums = [tuple(map(int, input().split())) for i in range(N)]

dirs = {"D" : (0, -1), "U": (0, 1), "L" : (-1, 0), "R" : (1, 0)}

opIdx = 0
for op in ops:
    (dx, dy) = dirs[op]
    opIdx += 1
    while not(curr in nums or abs(curr[0])  > 1000 or abs(curr[1]) > 1000):
        curr = (curr[0] + dx, curr[1] + dy)
        if curr == (0,0):
            break
    if curr == (0,0):
        break

    curr = (curr[0] - dx, curr[1] - dy)

if opIdx < len(ops):
    print("Arrived too early")
else:
    print(curr)
