B = int(input())

EPS = 0.0000001
INF = 1000000000000

def done(a, b):
    return (abs(a - b) < EPS) or (abs(a - b)/b < EPS)

percs = []
sizes = []
for i in range(B):
    size, perc = map(float, input().split(" "))
    sizes.append(size)
    percs.append(perc)

P = float(input())
F = int(input())

sizes.append(INF)
percs.append(P)

def take_home(amt):
    orig = amt
    tax = 0
    idx = 0
    while amt > 0:
        size = sizes[idx]
        perc = percs[idx]

        taxable = min(amt, size)
        tax += perc / 100 * taxable

        amt -= taxable
        idx += 1
    
    return orig - tax

for f in range(F):
    earned, targ = map(float, input().split())

    lo = 0
    hi = INF
    while not(done(lo, hi)):
        mi = (hi + lo) / 2
        gift_amt = take_home(earned + mi) - take_home(earned)
        if gift_amt - targ >= -EPS:
            hi = mi
        else:
            lo = mi

    print('{:.6f}'.format((hi + lo) / 2))
