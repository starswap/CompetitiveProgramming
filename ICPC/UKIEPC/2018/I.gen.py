from random import randint

def cafe():
    open = randint(1, 1000)
    close = randint(open, 1000)
    wifi = randint(1, 1000)
    return (open, close, wifi)

D = 200 # randint(1, 100)
N = 100 # randint(1, 4)
cafes = [cafe() for i in range(N)]
AM = [[randint(1, 10) if i != j else 0 for i in range(N)] for j in range(N)]

print(D)
print(N)
for cafe in cafes:
    print(*cafe)

for am in AM:
    print(*am)
