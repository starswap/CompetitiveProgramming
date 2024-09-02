import random
T = 10
MAX_N = 100000
MAX_A = 100000
with open("input.txt","w") as f:
    f.write(f"{T}\n")
    for t in range(T):
        n = random.randint(1, MAX_N)
        f.write(f"{n}\n")
        nums = [random.randint(1, MAX_A) for i in range(n)]
        f.write(" ".join(map(str, nums)) + "\n")

        
