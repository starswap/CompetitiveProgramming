number = input()[::-1]
dp = [[-1, -1] for i in range(len(number))]

def solve(i, pushing):
    if i == len(number):    
        return 0
    elif dp[i][pushing] != -1:
        return dp[i][pushing]
    else:
        char = number[i]
        play_cost = int(char) + solve(i + 1, 0)
        push_cost = (8 if pushing else 10) - int(char) + 1 + solve(i + 1, 1)
        dp[i][pushing] = min(play_cost, push_cost)
        return dp[i][pushing]

print(solve(0, 0))