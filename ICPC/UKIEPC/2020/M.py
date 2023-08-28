N = int(input())
a = [*map(int, input().split())]
b = [*map(int, input().split())]
c = [*map(int, input().split())]

res = []
for (i, j, k) in zip(a, b, c):
    res.append(sorted([i, j, k])[1])
print(" ".join(map(str, res)))