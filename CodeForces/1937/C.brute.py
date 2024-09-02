N = 35
bestXOR = 0
bestRes = []
for i in range(N):
    for j in range(N):
        if i ^ j > bestXOR:
            bestRes = [(i, j)]
            bestXOR = i ^ j
        elif i ^ j == bestXOR:
            bestRes.append((i, j))
            
print(bestRes)
print(bestXOR)

# from math import floor, log2

# for N in range(100):
#     ans = 0
#     for i in range(1, N):
#         ans += floor(log2(i)) + 1
#     print(ans, 3 * N)
#     print(ans <= 3 * N)