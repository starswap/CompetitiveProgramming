import random
T = 100
print(T)

for t in range(T):
    N = (t + 1) * 100
    print(N)

    first_half = 4 * N // 5 - 1
    for i in range(first_half):
        print(i + 5, i + 5)
    for i in range(N - first_half):
        x = random.randint(1, 100)
        y = random.randint(1, 100)
        print(x, y)
