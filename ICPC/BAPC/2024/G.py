N = int(input())
prices = [*map(lambda x : round(float(x) * 100), input().split())]

cost = 0
nthrees = 0
nfours = 0

for price in prices:
    if price % 5 in (0, 1, 2):
        cost += price
        cost -= price % 5
    elif price % 5 == 3:
        nthrees += 1
        cost += price
    else:
        nfours += 1
        cost += price

cost -= min(nthrees, nfours) * 2
if nthrees > nfours:
    remaining_threes = nthrees - nfours
    cost -= remaining_threes // 2
else:
    remaining_fours = nfours - nthrees
    cost -= (remaining_fours // 3) * 2

cost /= 100
print(f"{cost:.2f}")
