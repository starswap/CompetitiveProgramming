T = int(input())

def avg(x, y):
    return (x + y) / 2

for t in range(T):
    N = int(input())
    elves = [*map(int, input().split())]
    elves.sort()
    if N == 5:
        ans = max(avg(elves[4], elves[3]) - avg(elves[2], elves[0]), avg(elves[4], elves[2]) - avg(elves[1], elves[0]))
    else:
        ans = avg(elves[N - 1], elves[N - 2]) - avg(elves[1], elves[0])
    print(f"Case #{t + 1}: {ans}")