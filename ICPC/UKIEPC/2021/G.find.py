import random
BLOCK_SIZE = 16
MOD = 1000000007
a = [random.randint(1000,500000) for i in range(BLOCK_SIZE)]

results = set([])
for i in range(1 << BLOCK_SIZE):
    acc = 0
    for j in range(BLOCK_SIZE):
        operation = ((1 << j) & i) >> j
        if operation == 0:
            acc *= a[j]
        else:
            acc += a[j]
        acc %= MOD

    results.add(acc)
print(a)
print(1 << BLOCK_SIZE)
print(len(results))
    