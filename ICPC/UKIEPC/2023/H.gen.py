import random


N = 300000 #random.randint(1, 100)
Q = 300000  # random.randint(1, 100)
nums = [random.randint(-100000000, 100000000) for i in range(N)]

def query():
    if random.random() < 0.5:
        l = random.randint(1, N)
        r = random.randint(l, N)
        return ("check", l, r)
    else:
        l = random.randint(1, N)
        r = random.randint(l, N)
        d = random.randint(-200, 200)
        return ("update", l, r, d)

def tostr(query):
    return " ".join(map(str, query))

queries = [tostr(query()) for i in range(Q)]

print(N)
print(*nums)
print(Q)
print("\n".join(queries))
