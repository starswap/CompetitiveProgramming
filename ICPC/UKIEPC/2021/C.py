n, m = map(int, input().split())
grid = []
for i in range(n):
    grid.append(input())
grid = grid[::-1]
INF = 1000000000

dp = [[INF for i in range((1 << (m - 1)))] for i in range(n)]

def bit_count(number):
    cnt = 0
    for i in range(32):
        if number == 0:
            return cnt
        else:
            cnt += number & 1
            number >>= 1


def get_config(uncovered):
    def get_config_internal(idx):
        if idx == -1:
            yield []
        else:
            for i in range(-1, 2, 1):
                if uncovered[idx] + i >= 0 and uncovered[idx] + i < m - 1:
                    for item in get_config_internal(idx - 1):
                        yield item + [i]

    return get_config_internal(len(uncovered) - 1)

def check_valid_covering(to_cover):
    prev = False
    config_fail = False
    for i in range(m - 1):
        if to_cover & (1 << i):
            if prev:
                return False
            prev = True
        else:
            prev = False
    return True

def do_DP(to_support, row):
    global dp
    if row == -2:
        return 0
    elif dp[row][to_support] != INF:
        return dp[row][to_support]
    else:
        groups = []
        start = None
        for i in range(m):
            if grid[row][i] == '.' and grid[row + 1][i] == '.' and start != None:
                groups.append((start, i - 1))    
                start = None
            elif (grid[row][i] == '#' or grid[row + 1][i] == '#') and start == None:
                start = i
        
        if start != None:
            groups.append((start, i))
        
        best = INF

        for config in range(1 << len(groups)): # can push to the left or right
            to_cover = 0
            config_fail = False
            for i, (s, e) in enumerate(groups):
                start_mod = (config & (1 << i)) >> (i)
                end_mod = (1 - start_mod) if (e - s + 1) % 2 == 1 else start_mod
                if s - start_mod <= - 1 or e + end_mod == m: # doesn't fit
                    config_fail = True
                    break
                for i in range(s - start_mod, e + end_mod + 1, 2):
                    to_cover |= (1 << i)
            
            if not(check_valid_covering(to_cover)) or config_fail:
                continue
            
            uncovered = []
            for i in range(m - 1):
                if (1 << i) & to_support and not ((1 << i) & to_cover) and not (i -1 >= 0 and (1 << (i - 1)) & to_cover) and not (i + 1 < m - 1 and (1 << (i + 1)) & to_cover):
                    uncovered.append(i)

            for config in get_config(uncovered):
                all_covering = to_cover
                for i in range(len(config)):
                    all_covering |= (1 << (config[i] + uncovered[i]))

                if check_valid_covering(all_covering):
                    best = min(best, do_DP(all_covering, row - 2) + bit_count(all_covering))
        dp[row][to_support] = best
        return best

def printCover(to_cover):
    cans = "." * m
    for i in range(m - 1):
        if (1 << i) & to_cover:
            cans = cans[:i] + '@@' + cans[i + 2:]
    print(cans)
    print(cans)

def printDP(to_support, row):
    global dp
    if row == -2:
        return 0
    else:
        groups = []
        start = None
        for i in range(m):
            if grid[row][i] == '.' and grid[row + 1][i] == '.' and start != None:
                groups.append((start, i - 1))    
                start = None
            elif (grid[row][i] == '#' or grid[row + 1][i] == '#') and start == None:
                start = i
        
        if start != None:
            groups.append((start, i))
        
        best = INF

        for config in range(1 << len(groups)): # can push to the left or right
            to_cover = 0
            config_fail = False
            for i, (s, e) in enumerate(groups):
                start_mod = (config & (1 << i)) >> (i)
                end_mod = (1 - start_mod) if (e - s + 1) % 2 == 1 else start_mod
                if s - start_mod <= - 1 or e + end_mod == m: # doesn't fit
                    config_fail = True
                    break
                for i in range(s - start_mod, e + end_mod + 1, 2):
                    to_cover |= (1 << i)
            
            if not(check_valid_covering(to_cover)) or config_fail:
                continue
            
            uncovered = []
            for i in range(m - 1):
                if (1 << i) & to_support and not ((1 << i) & to_cover) and not (i -1 >= 0 and (1 << (i - 1)) & to_cover) and not (i + 1 < m - 1 and (1 << (i + 1)) & to_cover):
                    uncovered.append(i)
            
            for config in get_config(uncovered):
                all_covering = to_cover
                for i in range(len(config)):
                    all_covering |= (1 << (config[i] + uncovered[i]))
                if check_valid_covering(all_covering) and do_DP(all_covering, row - 2) + bit_count(all_covering) == dp[row][to_support]:
                    printCover(all_covering)
                    printDP(all_covering, row - 2)
                    return

print(do_DP(0, n - 2))
# printDP(0, n - 2)