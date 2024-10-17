xs, ys = list(map(int, input().split()))
xt, yt = list(map(int, input().split()))
xp, yp = list(map(int, input().split()))

ans = []
big = int(1e8)
if yp >= ys:
    ans.append((xs, -big))
    # Same direction as
    side = 1 if xt >= xs else -1            
    ans.append((big*side, -big))
    ans.append((big*side, yt))
    ans.append((xt, yt))
else:
    ans.append((xs, big))
    # Same direction as
    side = 1 if xt >= xs else -1
    ans.append((big*side, big))
    ans.append((big*side, yt))c
    ans.append((xt, yt))
print(len(ans))
for x,y in ans:
    print(x, y)