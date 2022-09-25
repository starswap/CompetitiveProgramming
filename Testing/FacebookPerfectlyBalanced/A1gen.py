import random

random.seed(100)

TCs = 1000
minN = 1 # 1000000
maxN = 100 # 1000000

minQ = 1 # 1000000
maxQ = 100 # 1000000

ALPHA = "abcdefghijklmnopqrstuvwxyz"

print(TCs)
for t in range(TCs):
    n = random.randint(minN,maxN)
    string = []
    for i in range(n):
        char = random.choice(ALPHA)
        string.append(char)

    print(''.join(string))

    q = random.randint(minQ,maxQ)
    print(q)
    for i in range(q):
        A = random.randint(1,n)
        B = random.randint(A,n)

        print(f"{A} {B}")
    
    
    
