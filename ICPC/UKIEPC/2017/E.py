
n, m = map(int, input().split())
studentsByDept = [*map(int, input().split())]
capacities = [*map(int, input().split())]
rentalCosts = [*map(int, input().split())]

vals = sorted([*zip(studentsByDept, range(n))], reverse=True)

mapping = [-1]*n
mapped = set()
for needs, j in vals:
    minCost = 10000000
    alloc = -1

    for i in range(len(capacities)):
        cap = capacities[i]
        if cap >= needs and rentalCosts[i] < minCost and not(i in mapped):
            minCost = rentalCosts[i]
            alloc = i
    
    # if alloc == -1:
    #     break
    mapping[j] = alloc
    mapped.add(alloc)


if -1 in mapping:
    print("impossible")
else:
    print(" ".join(map(lambda x : str(x+1), mapping)))
