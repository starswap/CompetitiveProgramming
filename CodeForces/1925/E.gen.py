import random
N = 100
M = 10
Q = 100
Xs = [*range(2, N)]
random.shuffle(Xs)
Xs = Xs[:M - 2] + [1, N] 
print(f"{N} {M} {Q}")
print(*Xs)
Vs = [random.randint(1, 10000000) for i in range(M)]
print(*Vs)

placed = set(Xs)
for q in range(Q):
    done = False
    while not done:
        t = random.randint(1, 2)
        if t == 1:
            x = random.randint(2, N - 1)
            if x in placed:
                continue
            v = random.randint(1, 10000000)
            print(f"{t} {x} {v}")
            placed.add(x)
            done = True
        else:
            l = random.randint(1, N)
            r = random.randint(l, N)
            print(f"{t} {l} {r}")
            done = True
