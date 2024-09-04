from itertools import product
alpha = "abcdefghijklmnopqrstuvwxyz"

N = int(input())
names = product(alpha, repeat=5)

names_map = {
    "0.75": "standard",
    "15": "nebuchadnezzar",
    "12": "balthazar" 
}

for i in range(N):
    line = input()[:-1]
    for j in range(len(line)):
        if line[j] != '0':
            break

    if '.' in line:
        for k in range(len(line) - 1, -1, -1):
            if line[k] != '0':
                break
    else:
        k = len(line)

    line = line[j:k + 1]
    if line[-1] == '.':
        line = line[:-1]
    if line in names_map:
        print(names_map[line])
    else:
        name = "".join(next(names))
        print(name)
        names_map[line] = name 
    