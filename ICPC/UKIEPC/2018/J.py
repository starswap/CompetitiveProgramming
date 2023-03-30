from math import sqrt
nums = input().split()
n = int(nums[0])
m = int(nums[1])
f = float(nums[2])

canConsider = [0, n - 1]

if 4 * n * n - 4 * 1 * m / (f * f) >= 0:
    d1 = int(round((2 * n - sqrt(4 * n * n - 4 * 1 * m / (f * f))) / 2))
    if (d1 >= 0 and d1 < n):
        canConsider.append(d1)

maxi = 0
for d in canConsider:
    maxi = max(maxi, (m - d * d * f * f) / (n - d))

print(maxi)
