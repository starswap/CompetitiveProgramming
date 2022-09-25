import random
random.seed(10)

RAND_MIN = 10000000
RAND_MAX = 10000000000

ALPHA = "abcdefghijklmnopqrstuvwxyz"
mapping = {}
randoms = set([])

for letter in ALPHA:
    number = random.randint(RAND_MIN,RAND_MAX)
    mapping[letter] = number
    randoms.add(number)

def getRangeHash(start,end):
    if start == 0:
        loss = 0
    else:
        loss = partialSums[start-1]
        
    return partialSums[end] - loss

def checkDiff(a_start,a_end,b_start,b_end):
    a_hash = getRangeHash(a_start,a_end)
    b_hash = getRangeHash(b_start,b_end)
    return ((a_end - a_start > b_end - b_start) and (a_hash - b_hash in randoms)) or ((a_end - a_start < b_end - b_start) and (b_hash - a_hash in randoms))

TCs = int(input())
for t in range(TCs):
    string = input()
    Q = int(input())
    queries = []
    for q in range(Q):
        A,B = map(int,input().split())
        queries.append((A-1,B-1))
    
    partialSums = []
    partialSum = 0

    for char in string:
        partialSum += mapping[char]
        partialSums.append(partialSum)

    totalAlmostPerfect = 0

    for (A,B) in queries:
        delta = B-A
        if (delta % 2 == 0):
            totalAlmostPerfect += int(checkDiff(A,A+delta//2-1,A+delta//2,B) or checkDiff(A,A+delta//2,A+delta//2+1,B))

    print(f"Case #{t+1}: {totalAlmostPerfect}")
    
