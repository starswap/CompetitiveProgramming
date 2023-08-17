n, p = map(int, input().split())
team_pens = []
for i in range(n):
    pen = int(input())
    team_pens.append(pen)
team_pens = team_pens[::-1]

scores = []
if team_pens[0] == 0:
    scores.append(0)
else:
    scores.append(1)

for i in range(1, n): 
    if team_pens[i] > team_pens[i - 1]:
        scores.append(scores[-1] + 1)
    else:
        scores.append(scores[-1])

if scores[-1] == p or all(map(lambda x : x == 0, team_pens)):
    print("\n".join(map(str, scores[::-1])))
else:
    print("ambiguous")