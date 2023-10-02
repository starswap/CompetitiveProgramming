M = len(input().split())
N = int(input())
names = [input() for i in range(N)]
teams = [[], []]
curr = 0
team = 0

while len(names) != 0:
    for i in range(M - 1):
        curr += 1
        curr %= N
    
    teams[team].append(names[curr])
    del names[curr]
    N -= 1

    team += 1
    team %= 2

for i in range(2):
    print(len(teams[i]))
    for name in teams[i]:
        print(name)
