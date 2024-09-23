import random
T = 100
print(T)
for t in range(T):
    N = 4 # random.randint(1, 5)
    G = random.randint(1, 10)
    print(N, G)
    for n in range(N):
        print(random.randint(N, 10))
