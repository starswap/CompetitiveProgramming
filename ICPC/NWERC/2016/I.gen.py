import random
N_MIN = 2
N_MAX = 1000000
n = random.randint(N_MIN, N_MAX)

M_MIN = 1
M_MAX = n
m = random.randint(M_MIN, M_MAX)

K_MIN = 1
K_MAX = n
k = random.randint(K_MIN, K_MAX)

print(f"{n} {m} {k}")
nodes = [*range(1, n + 1)]
# random.shuffle(nodes)
print(" ".join(map(str, nodes[:m])))

# random.shuffle(nodes)
print(" ".join(map(str, nodes[:k])))

for i in range(n):
    a = random.randint(0, min(n, 10))
    print(f"{a} ", end="")
    # random.shuffle(nodes)
    print(" ".join(map(str, nodes[:a])))

