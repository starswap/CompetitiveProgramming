from collections import Counter
N, M = map(int, input().split())
strings = []
for n in range(N):
    strings.append(input())

res = []
for j in range(M):
    choices = []
    for i in range(N):
        choices.append(strings[i][j])
    
    letter = ""
    best = 0
    for (i, count) in Counter(choices).items():
        if count > best or count == best and i < letter: 
            best = count
            letter = i
    res += letter
print("".join(res))