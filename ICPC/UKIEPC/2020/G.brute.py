N, M = map(int, input().split())
INF = 1e16

plant_cost = [INF for i in range(N)]
for i in range(M):
    c, a = map(int, input().split())
    c -= 1
    plant_cost[c] = a

wire_cost = [*map(int, input().split())]

def get_answer(lastOne, minimumSoFar, current):
    if lastOne == current:
        return min(minimumSoFar, plant_cost[current])
    else:
        # try continuing current
        continueScore = get_answer(lastOne, min(minimumSoFar, plant_cost[current]), (current + 1) % N) + wire_cost[current]
        # try separating
        breakScore = get_answer(lastOne, INF, (current + 1) % N) + min(minimumSoFar, plant_cost[current])
        return min(continueScore, breakScore)

ans = INF
for i in range(N):
    ans = min(ans, get_answer(i, INF, (i + 1) % N))
print(ans)