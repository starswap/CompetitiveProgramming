import itertools

B = int(input())
amtNeeded = list(map(int,input().split()))
T = int(input())
farmersCovered = [set() for _ in range(B)]

for t in range(T):
    thisFarmerHas = list(map(int,input().split()))[1:]
    for num in thisFarmerHas:
        num -= 1
        farmersCovered[num].add(t)
    if len(thisFarmerHas) == 0:
        for num in range(0,B):
            farmersCovered[num].add(t)


best = 10000000

for n in range(B+1):
    for subset in itertools.combinations(list(range(0,B)),n):
        current = set()
         
        total = sum(map(lambda a : amtNeeded[a], subset))

        for selected in subset:
            current = current.union(farmersCovered[selected])

        if list(current) == list(range(0,T)):
            best = min(best,total)

print(sum(amtNeeded) - best)
