m, b, s = map(int, input().split())

canVis = set()
for i in range(b):
    route = input()
    if (route[m - 1] == "1"):
        for i,d in enumerate(route):
            if d == "1" and i != m - 1:
                canVis.add(i)
    
print(len(canVis))
