import random
M = 1000

print(M)
numbers = [i + 1 for i in range(M)]
random.shuffle(numbers)
shorts = numbers[:M // 2]
talls = numbers[M // 2:]

pairs = [(x, (0, random.choice(talls))) for x in shorts] + [(x, (1, random.choice(shorts))) for x in talls]
answer = {x: y for (x, y) in pairs}

for i in range(M):
    print(*answer[i + 1])


# import random
# M = 100000

# print(M)
# for i in range(M):
#     print(f"{i % 2} {(i // 100 + 1) * 100}")

# import random
# M = 100000

# print(M)
# for i in range(M):
#     print(f"{i % 2} 99999")
