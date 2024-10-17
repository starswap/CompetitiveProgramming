n,sh = list(map(int, input().split()))

tot = 0
can = True
for i in range(n):
    sides = sorted(map(int, input().split()), reverse=True)
    
    for x in sides:
        if x <= sh:
            sides.remove(x)
            break
    if len(sides) == 3:
        print("impossible")
        can = False
        break
    tot += min(sides)
if can:
    print(tot)
