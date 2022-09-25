import random

random.seed(100)

TCs = 4

minN = 1000000
maxN = 1000000

minM = 1 #1000000
maxM = 1000000

minQ = 1000000
maxQ = 1000000

chanceOfType2 = 0.8

print(TCs)
for t in range(TCs):
    n = random.randint(minN,maxN)
    string = []
    print(n)
    for i in range(n):
        string.append(random.randint(minM,maxM))

    print(' '.join(map(str,string)))

    q = random.randint(minQ,maxQ)
    print(q)
    for i in range(q):
        if random.random() < chanceOfType2: #type 2
            A = random.randint(1,n)
            B = random.randint(A,n)
            print(f"2 {A} {B}")
        else: #type 1
            A = random.randint(1,n)
            B = random.randint(minM,maxM)
            print(f"1 {A} {B}")
    
    
    
