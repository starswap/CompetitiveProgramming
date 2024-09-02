import random
N = 6
S = random.randint(5, 20)
print(f"{N} {S}")
nums = [random.randint(3, max(3, S // 2)) for i in range(N)]
print(*nums)
