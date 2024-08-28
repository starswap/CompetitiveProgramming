
import random

N = random.randint(1, 30)
C = random.randint(1, 30)
songs = [random.randint(1, 30) for i in range(N)]

print(N, C)
print(*songs)
