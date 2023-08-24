import random
N_MIN = 3
N_MAX =  5
n = random.randint(N_MIN, N_MAX)

M_MIN = 3
M_MAX = n
m = random.randint(M_MIN, M_MAX)

print(f"{n} {m}")

MIN_COST = 1
MAX_COST = 100 # 1000

posns = [*range(1, n + 1)]
random.shuffle(posns)
posns = sorted(posns[:m])

for i in range(m):
    c = posns[i]
    a = random.randint(MIN_COST, MAX_COST)
    print(f"{c} {a}")

costs = [random.randint(MIN_COST, MAX_COST) for i in range(n)]
print(' '.join(map(str, costs)))
