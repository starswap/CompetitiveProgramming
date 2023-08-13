import bisect

B = int(input())

EPS = 0.0000001
INF = 100000000000000

percs = []
sizes = []
bounds = []
acc = 0
for i in range(B):
    size, perc = map(float, input().split(" "))
    sizes.append(size)
    percs.append(perc)
    acc += size
    bounds.append(acc)

P = float(input())
F = int(input())

sizes.append(INF)
percs.append(P)
bounds.append(INF)

for f in range(F):
    earned, targ = map(float, input().split())
    tax = 0
    current_income = earned
    amt_left = targ

    current_band = bisect.bisect_left(bounds, earned)

    while amt_left > 0:
        left_in_band = bounds[current_band] - current_income
        total_incl_tax = INF if percs[current_band] == 100 else (amt_left) / (1 - percs[current_band] / 100)
        
        if total_incl_tax < left_in_band: # can fit all in this band
            tax += total_incl_tax - amt_left
            amt_left = 0
        else:
            amt_left -= left_in_band
            marg_tax = left_in_band * percs[current_band] / 100
            amt_left += marg_tax
            tax += marg_tax
            current_income = bounds[current_band]
            current_band += 1

    print("{:.6f}".format(targ + tax))
