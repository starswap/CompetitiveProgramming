MAX_N = 20

facts = [1]
for i in range(1, MAX_N + 1):
    facts.append(i * facts[-1])

a = [-100, 0, 1]

for i in range(3, MAX_N + 1):
    a.append((a[-1] + a[-2]) * (i - 1))

N = int(input())
N = min(MAX_N, N)
print((facts[N] - a[N]) / facts[N])