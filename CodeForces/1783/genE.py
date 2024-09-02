import random
T = 100
MIN_N = 1
MAX_N = 10
with open("input.txt", "w") as f:
    f.write(f"{T}\n")
    for t in range(T):
        n = random.randint(MIN_N, MAX_N)
        f.write(f"{n}\n")
        a = [random.randint(1, n) for i in range(n)]
        b = [random.randint(1, n) for i in range(n)]
        f.write(" ".join(map(str, a)) + "\n")
        f.write(" ".join(map(str, b)) + "\n")
