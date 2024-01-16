N = int(input())
Ds = [*map(int, input().split())]
maxi = 0
h = 0
for d in Ds:
    h += d
    maxi = max(maxi, h)

h = 0
sol = 0
for d in Ds:
    h += d
    sol = max(sol, d)
    if h == maxi:
        break
print(sol)