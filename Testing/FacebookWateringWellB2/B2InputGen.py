import random
T = 1

N_MIN = 500000
N_MAX = 500000

Q_MIN = 500000
Q_MAX = 500000

MAX_COORD = 1000000000
MIN_COORD = 0

random.seed(8000)

print(T)
for t in range(T):
    N = random.randint(N_MIN,N_MAX)
    print(N)
    for n in range(N):
        x = random.randint(MIN_COORD,MAX_COORD)
        y = random.randint(MIN_COORD,MAX_COORD)
        print(f"{x} {y}")
    
    Q = random.randint(Q_MIN,Q_MAX)
    print(Q)
    for q in range(Q):
        x = random.randint(MIN_COORD,MAX_COORD)
        y = random.randint(MIN_COORD,MAX_COORD)
        print(f"{x} {y}")    


