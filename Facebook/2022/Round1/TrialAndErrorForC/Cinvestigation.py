import itertools

#points = [(5.15,-3.07),(-3.2,1.8),(-5.7,-2.75),(1.1,5),(-0.42,-5.06),(5.9,-1.23)]
points = [(15.58,-3.13),(-3.2,1.8),(-5.7,-2.75),(8.77,2.84),(1.1,5),(-0.42,-5.06),(-0.08,4),(17.48,-1.58)]
points.sort()

INF = 10000000000

intermediates = points[1:-1]
MaxScoresByLength = [0 for i in range(len(points)+1)]
MinScoresByLength = [INF for i in range(len(points)+1)]

bestScore = INF

for comb in itertools.chain(*[itertools.permutations(intermediates,r) for r in range(1,len(intermediates)+1)]):
    comb = list(comb)
    route = [points[0]] + comb + [points[-1]]
    score = 0
    for i in range(len(route)-1):
        x_prev,y_prev = route[i]
        x_next,y_next = route[i+1]
        score += (y_prev-y_next)**2 + (x_next-x_prev)**2

    
    MaxScoresByLength[len(route)] = max(MaxScoresByLength[len(route)],score)
    if score < bestScore:
        bestScore = score
        bestRoute = route

    MinScoresByLength[len(route)] = min(MinScoresByLength[len(route)],score)

print("Max" + str(MaxScoresByLength))
print("Min " + str(MinScoresByLength))
print(bestRoute)
