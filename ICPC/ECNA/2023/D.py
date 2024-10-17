nums = [*map(int, input().split())]
N, K = map(int, input().split())

S = 0
for i in range(5):
    S += nums[2 * i] * nums[2 * i + 1]
S //= 5

ans = (S * N) // K
print(ans)