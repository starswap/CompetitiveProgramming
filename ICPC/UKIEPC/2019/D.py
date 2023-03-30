from math import sqrt
def hypot(x, y, z):
    return sqrt(x**2 + y**2 + z**2)
n, k = map(int, input().split())
print(sorted([(hypot(*map(float, input().split()))) for i in range(n)])[k - 1])
