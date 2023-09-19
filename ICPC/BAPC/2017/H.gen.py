import random
N = 4
print(N)
for i in range(N):
    numbs = [random.randint(-1000000000, 1000000000) for i in range(4)]
    print(" ".join(map(str, numbs)))
