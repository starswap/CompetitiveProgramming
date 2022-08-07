import random

TCs = 10
MIN_N = 200000 #2
MAX_N = 200000
MAX_L = 200000 #200000

with open("input.txt", "w") as f:
  f.write(f"{TCs}\n")
  for t in range(TCs):
    n = random.randint(MIN_N,MAX_N)
    k = random.randint(min(n-2,25),n-2)
    f.write(f"{n} {k}\n")
    numbers = []
    for i in range(n):
      number = random.randint(1,MAX_L)
      numbers.append(number)
    f.write(f'{" ".join(list(map(str,numbers)))}\n')
