def get_min(line):
    total = line.count("1")
    pairs = 0
    i = 0
    while i < M - 1:
        if pairs < M // 4 and line[i] == line[i + 1] and line[i] == "1":
            pairs += 1
            i += 1
        i += 1
    return total - pairs

def get_max(line):
    total = line.count("1")
    pairs = 0
    i = 0
    while i < M - 1:
        if pairs < M // 4 and not(line[i] == line[i + 1] and line[i] == "1"):
            pairs += 1
            i += 1
        i += 1
    return total - (M // 4 - pairs)

N, M = map(int, input().split())
A = [input() for i in range(N)]

mini = sum(map(get_min, A))
maxi = sum(map(get_max, A))
print(mini, maxi)
