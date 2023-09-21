import math

line = input().split()
people = int(line[0])
lives = int(line[1])
q = float(line[2])
p = 1 - q

def getp(x, p, N):
    """Returns P(x = X) for a binomial distribution X ~ B(N, p)"""
    return math.comb(N, x) * (p**x) * ((1-p)**(N - x))

def getP(x, p, N):
    """Returns P(x < X) for a binomial distribution X ~ B(N, p)"""
    q = 0
    for i in range(x):
        q += getp(i, p, N)
    return q

ans = 0
last = 0
for N in range(lives, 850):
    # people * p(<lives, in N) * (P(>= lives in N) - so_far)
    # = people * p(<lives in N) * (P(>= lives in N) for everyone - P(>= lives in N - 1) for everyone)
    prob = getP(lives, p, N)
    ans += people * (prob) * ((1-prob)**(people - 1) - last**(people - 1))
    last = (1 - prob) # cache

print(f"{1 - ans:.7f}")