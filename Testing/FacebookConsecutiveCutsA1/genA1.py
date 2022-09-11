import random
T = 1000
print(T)
minK = 1
maxK = 1e9


for t in range(T):
    N = random.randint(2,8)
    K = random.randint(minK,maxK)
    print(f"{N} {K}")
    A = list(range(1,N+1))
    B = list(range(1,N+1))
    random.shuffle(A)
    random.shuffle(B)
    print(" ".join(map(str,A)))
    print(" ".join(map(str,B)))
