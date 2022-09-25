import random
from sys import stdin, stdout

random.seed(299)

class FTree:
    """Thanks steven"""
    def __init__(self, f):
        self.n = len(f)
        self.ft = [0] * (self.n + 1)

        for i in range(1, self.n + 1):
            self.ft[i] += f[i - 1]
            if i + self.lsone(i) <= self.n:
                self.ft[i + self.lsone(i)] += self.ft[i]

    def lsone(self, s):
        return s & (-s)

    def query(self, i, j):
        if i > 1:
            return self.query(1, j) - self.query(1, i - 1)

        s = 0
        while j > 0:
            s += self.ft[j]
            j -= self.lsone(j)

        return s

    def update(self, i, v):
        while i <= self.n:
            self.ft[i] += v
            i += self.lsone(i)

    def select(self, k):
        p = 1
        while (p * 2) <= self.n: p *= 2

        i = 0
        while p > 0:
            if k > self.ft[i + p]:
                k -= self.ft[i + p]
                i += p
            p //= 2

        return i + 1


#ft.update(index, value)
#ft.query(start,end+1)
#doesn't include the last one

RAND_MIN = 10000000
RAND_MAX = 1000000000000

mapping = {}
randoms = set([])


def checkDiff(a_start,a_end,b_start,b_end):
    a_hash = ft.query(a_start,a_end)
    b_hash = ft.query(b_start,b_end)
    
    return ((a_end - a_start > b_end - b_start) and (a_hash - b_hash in randoms)) or ((a_end - a_start < b_end - b_start) and (b_hash - a_hash in randoms))

TCs = int(stdin.readline())
for t in range(TCs):
    N = int(stdin.readline())
    numbers = map(int,stdin.readline().split())
    mappedOut = []
    for num in numbers:
        if not(num in mapping):
            mapped = random.randint(RAND_MIN,RAND_MAX)
            mapping[num] = mapped
            randoms.add(mapped)
        mappedOut.append(mapping[num])

    ft = FTree(mappedOut)
    
    Q = int(stdin.readline())
    queries = []

    for q in range(Q):
        queryType,A,B = map(int,stdin.readline().split())
        queries.append((queryType,A,B))
        if queryType == 1:
            if not(B in mapping):
                mapped = random.randint(RAND_MIN,RAND_MAX)
                mapping[B] = mapped
                randoms.add(mapped)

    totalAlmostPerfect = 0

    for (queryType,A,B) in queries:
        if queryType == 1:
#            print(A-1)
 #           print(mapping[B])
            ft.update(A,-mappedOut[A-1])
            ft.update(A,mapping[B])
            mappedOut[A-1] = mapping[B]

        elif queryType == 2:
            A = A
            B = B
            delta = B-A
            if (delta % 2 == 0):
                totalAlmostPerfect += int(checkDiff(A,A+delta//2-1,A+delta//2,B) or checkDiff(A,A+delta//2,A+delta//2+1,B))

    stdout.write(f"Case #{t+1}: {totalAlmostPerfect}\n")
    
