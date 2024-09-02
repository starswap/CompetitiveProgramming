from itertools import combinations

string = input()
N = len(string)
D = [[0 for i in range(N)] for j in range(N)]
for i in range(N):
    line = map(int, input().split())
    for item, j in zip(line, range(i, N)):
        D[i][j] = item
        D[j][i] = item

def get_score(comb):
    score = 0
    for i in comb:
        for j in comb:
            if i > j:
                continue
            score += D[i][j]

    return score

best_score = -1000000
best_comb = None
for i in range(0, N + 1):
    for comb in combinations(range(N), i):
        score = get_score(comb)
        if score > best_score:
            best_score = score
            best_comb = comb
        elif score == best_score:
            print(best_score, comb)

print(len(best_comb))
if best_comb:
    print("".join([string[i] for i in best_comb]))
print(best_score)
