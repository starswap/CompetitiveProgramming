import random
N = 100
Q = 100
a = "".join(map(str, [random.randint(0, 1) for i in range(N)]))
print(N, Q)
print(a)
for i in range(Q):
    T = random.randint(1, 3)
    L = random.randint(1, N)
    R = random.randint(L, N)
    print(T, L, R)