import random
n, m, c = map(int, input().split())

# check both Robin methods

class Hash:
    def __init__(self, hashes):
        self.hashes = hashes
    def __hash__(self) -> int:
        return self.hashes.__hash__()
    def __eq__(self, other):
        return self.hashes == other.hashes
    def __add__(self, other):
        return Hash((self.hashes[0] + other.hashes[0], self.hashes[1] + other.hashes[1]))
    def __sub__(self, other):
        return Hash((self.hashes[0] - other.hashes[0], self.hashes[1] - other.hashes[1]))

class Hasher:
    def __init__(self):
        self.colours1 = [random.randint(100000000, 1000000000) for i in range(c)]
        self.colours2 = [random.randint(100000000, 1000000000) for i in range(c)]

    def compute_with(self, row, colours):
        counts = count(row)
        zeroed = [*map(lambda x : x - counts[0], counts)]
        hashed = sum(map(lambda x, y : x * y, zeroed, colours))
        return hashed

    def compute(self, row):
        return Hash((self.compute_with(row, self.colours1), self.compute_with(row, self.colours2)))

def LSOne(x):
    return x & -x

def count(it):
    counts = [0 for i in range(c)]
    for item in it:
        counts[item - 1] += 1
    return counts

def ctz(x):
    mask = 1
    cnt = 0
    while not(mask & x):
        cnt += 1
        mask <<= 1
    return cnt

if n == 1:
    nums = map(int, input().split())
    counts = count(nums)
    if (all(map(lambda x : x == counts[0], counts))):
        print(1)
    else:
        print(0)
else:
    hasher = Hasher()
    row_hashes = []
    for row in range(n):
        nums = [*map(int, input().split())]
        row_hashes.append(hasher.compute(nums))
    
    f = n // 2
    top_half_lookup = {}
    mask = 0
    hash = Hash((0, 0))
    cnt = 0
    for i in range(1, 1 << f):
        if hash in top_half_lookup:
            top_half_lookup[hash] = max(top_half_lookup[hash], cnt)
        else:
            top_half_lookup[hash] = cnt
        if LSOne(i) & mask:
            cnt -= 1
            hash -= row_hashes[ctz(LSOne(i))]
        else:
            cnt += 1
            hash += row_hashes[ctz(LSOne(i))]
        mask ^= LSOne(i)
    
    if hash in top_half_lookup:
        top_half_lookup[hash] = max(top_half_lookup[hash], cnt)
    else:
        top_half_lookup[hash] = cnt
    e = n - f
    mask = 0
    target_hash = Hash((0, 0))
    cnt = 0
    best = 0
    for i in range(1, 1 << e):
        if target_hash in top_half_lookup:
            best = max(best, top_half_lookup[target_hash] + cnt)
        
        if LSOne(i) & mask:
            cnt -= 1
            target_hash += row_hashes[f + ctz(LSOne(i))]
        else:
            cnt += 1
            target_hash -= row_hashes[f + ctz(LSOne(i))]
        mask ^= LSOne(i)
    
    if target_hash in top_half_lookup:
        best = max(best, top_half_lookup[target_hash] + cnt)

    print(best)

