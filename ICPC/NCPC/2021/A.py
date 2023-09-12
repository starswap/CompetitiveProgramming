n, c = map(int, input().split())
x = [*map(int, input().split())]

H = 0
L = 0
ans = [0]

def score(x, i, j, c):
    return abs(x[i] - x[j]) - c * abs(i - j)

for i in range(1, n):
    hi_pot_H = x[H] - x[i] - (i - H) * c
    lo_pot_L = x[i] - x[L] - (i - L) * c

    if hi_pot_H <= 0:
        H = i
    if lo_pot_L <= 0:
        L = i
    ans.append(max(score(x, i, H, c), score(x, i, L, c)))

print(" ".join(map(str, ans)))