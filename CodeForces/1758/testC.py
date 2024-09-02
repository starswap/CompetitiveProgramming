import random
MIN_N = 10000
MAX_N = 10000
with open("C2.in","w") as f:
    T = 100
    f.write(str(T) + "\n")
    for t in range(T):
        n = random.randint(MIN_N,MAX_N)
        x = random.randint(1, n)
        f.write(f"{n} {x}\n")
    