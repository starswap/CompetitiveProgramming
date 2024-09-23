import random
T = 4
print(T)

for t in range(T):
    N = 1000000 
    print(N)
    for i in range(N):
        x = random.randint(1, 100)
        y = random.randint(1, 100)
        print(x, y)
