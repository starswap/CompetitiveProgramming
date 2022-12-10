from math import ceil, sqrt

EPS = 0.000001

def safeCeil(x):
    if abs(round(x) - x) < EPS:
        return round(x)+1
    else:
        return ceil(x)

r = int(input())
bestX = 0
bestY = 0
bestVal = 10000000000
for x in range(1,r+1):
    y = safeCeil(sqrt(r**2 - x**2))
    dist = sqrt(x**2 + y**2)
    if (dist < bestVal):
        bestVal = dist
        bestX = x
        bestY = y


print(f"{bestX} {bestY}")