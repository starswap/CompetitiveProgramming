import random
MIN_N = 1
MAX_N = 30
# MIN_N = MAX_N

MIN_Q = 1
MAX_Q = 30
# MIN_Q = MAX_Q

MIN_S = 1
MAX_S = 100
# MIN_S = MAX_S

MIN_SIZE = 1
MAX_SIZE = 1000000
#  MIN_SIZE = MAX_SIZE

MIN_D = 1
MAX_D = 1000000
# MIN_D = MAX_D

MIN_A = 1
MAX_A = 1000000

n = random.randint(MIN_N, MAX_N)
q = random.randint(MIN_N, MAX_N)
s = random.randint(MIN_N, MAX_N)

print(f"{n} {q} {s}")
queue_i = []
for i in range(s):
    queue_i.append(random.randint(1, q))

print(" ".join(map(str, queue_i)))

queue_size = []
for i in range(q):
    queue_size.append(random.randint(MIN_SIZE, MAX_SIZE))
print(" ".join(map(str, queue_size)))

for i in range(n):
    d = random.randint(MIN_D, MAX_D)
    a = []
    for j in range(s):
        a.append(random.randint(MIN_A, MAX_A))
    
    print(" ".join(map(str, [d] + a)))

