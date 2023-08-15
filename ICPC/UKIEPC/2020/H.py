n = int(input())
inps = []
for i in range(n):
    m, *dishes = input().split()
    inps.append((m, dishes))

print(inps[0][0])
for dish in inps[0][1]:
    print(dish)