T = int(input())

dr = [0, 0, -1, 1]
dc = [1, -1, 0, 0]

def flood_fill(r, c, visited, grid):
    # print(visited)

    # if r == 1:
    #     print(r, c)
    if r < 0 or r >= R or c < 0 or c >= C:
        return True
    if grid[r][c] == '.':
        return False
    elif grid[r][c] == 'B':
        return True
    else: # white
        if visited[r][c]:
            return True 
        else:
            visited[r][c] = True
            ok = True
            for i in range(4):
                ok = ok and flood_fill(r + dr[i], c + dc[i], visited, grid)
            return ok
import copy
def can_remove(grid, R, C):
    for i in range(R):
        for j in range(C):
            # print(grid[i][j])
            visited = [[False for i in range(C)] for j in range(R)]
            # print(visited)
            if grid[i][j] == 'W' and not visited[i][j] and flood_fill(i, j, visited, grid):
                # print("Sucess")
                # printGrid(grid)
                # print(i,j)
                # print(visited[i][j])
                return True
    return False

def printGrid(grid):
    for row in grid:
        print("".join(row))
    print()

for t in range(T):
    R, C = map(int, input().split())
    grid = [list(input()) for i in range(R)]
    ans = False
    # ans = can_remove(grid, R, C)
    for r in range(R):
        for c in range(C):
            if grid[r][c] == '.':
                grid[r][c] = 'B'
                if can_remove(grid, R, C):
                    ans = True
                    break
                    # printGrid(grid)
                grid[r][c] = '.'
        if ans == True:
            break
    print(f"Case #{t + 1}: {'YES' if ans else 'NO'}")