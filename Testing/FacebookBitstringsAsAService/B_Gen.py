import random

TCs = 350

MIN_M = 100
MAX_M = 200

MIN_N = 4000
MAX_N = 4000

print(TCs)
for t in range(TCs):
    M = random.randint(MIN_M,MAX_M)
    N = random.randint(MIN_N,MAX_N)
    print(f"{N} {M}")
    for i in range(M):
        X = random.randint(1,N)
        Y = random.randint(X,N)
        print(f"{X} {Y}")
