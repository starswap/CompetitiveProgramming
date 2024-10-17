import random
M, N, K, S = map(int, input().split())
x1 = [*map(float, input().split())]
x2 = [*map(float, input().split())]
points = x1 + x2
maxi = max(*x1, *x2)
mini = min(*x1, *x2)

best = 100000000000000000
for i in range(100):
    # random.shuffle(points)
    ks = [random.random() * (maxi - mini) + mini for k in range(K)]

    while True:
        oldks = ks
        assignees = [[] for k in range(K)]

        for x in x1 + x2:
            best_k = 10000
            best_dist = 1000000000000000000
            for k in range(K):
                dist = (ks[k] - x)**2
                if dist < best_dist:
                    best_dist = dist
                    best_k = k
            assignees[best_k].append(x)
        
        for k in range(K):
            if len(assignees[k]) == 0:
                ks[k] = random.choice(points) #random.random() * (maxi - mini) + mini
            else:
                total_x = sum(assignees[k])
                new_x = total_x / len(assignees[k])
                ks[k] = new_x

        if oldks == ks:
            break
    else:
        print(1/0)
    dist = 0
    for k in range(K):
        for x in assignees[k]:
            dist += (x - ks[k]) ** 2 + (S / 2) ** 2
    best = min(best, dist)
    print(dist)
print(best)
