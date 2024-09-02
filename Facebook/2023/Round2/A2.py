import sys
sys.setrecursionlimit(10000)
T = int(input())

dr = [0, 0, -1, 1]
dc = [1, -1, 0, 0]

def flood_fill(r, c, visited, grid):
    if r < 0 or r >= R or c < 0 or c >= C or visited[r][c]:
        return (set([]), 0)
    elif grid[r][c] == '.':
        return (set([(r, c)]), 0)
    elif grid[r][c] == 'B':
        return (set([]), 0)
    else:
        visited[r][c] = True
        allstones = set([])
        all_to_kill = 0
        for i in range(4):
            (stones, to_kill) = flood_fill(r + dr[i], c + dc[i], visited, grid)
            all_to_kill += to_kill
            if len(allstones) <= 1:
                for item in stones:
                    allstones.add(item)
        return (allstones, all_to_kill + 1)

def printGrid(grid):
    for row in grid:
        print("".join(row))
    print()
from collections import defaultdict
for t in range(T):
    R, C = map(int, input().split())
    grid = [list(input()) for i in range(R)]
    ans = 0

    position_scores = defaultdict(int)

    visited = [[False for i in range(C)] for j in range(R)]
    for r in range(R):
        for c in range(C):
            if grid[r][c] == 'W' and not visited[r][c]:
                # print(r, c)
                (allstones, all_to_kill) = flood_fill(r, c, visited, grid)
                # print(allstones)
                # print(visited)
                if len(allstones) == 1:
                   position_scores[(list(allstones)[0])] += all_to_kill
    # print(position_scores)
    best = 0
    for posn, score in position_scores.items():
        best = max(best, score)
    print(f"Case #{t + 1}: {best}")