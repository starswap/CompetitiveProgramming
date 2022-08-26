import random

def pick():
  L = random.randint(1,MAX_CLEAR)
  R_1 = random.randint(1,N)
  C_1 = random.randint(1,3)
  while L < squares[R_1-1][C_1-1]:
    L = random.randint(1,MAX_CLEAR)
    R_1 = random.randint(1,N)
    C_1 = random.randint(1,3)
  
  R_2 = random.randint(1,N)
  C_2 = random.randint(1,3)
  while L < squares[R_2-1][C_2-1]:
    R_2 = random.randint(1,N)
    C_2 = random.randint(1,3)

  return L,R_1,C_1,R_2,C_2

TCs = 1000
MAX_N = 12
MAX_M = 12
MAX_CLEAR = 100000

print(f"{TCs}")
for i in range(TCs):
  N = random.randint(1,MAX_N)
  M = random.randint(1,MAX_M)
  print(f"{N} {M}")
  squares = []
  for n in range(N):
    A_1 = random.randint(1,MAX_CLEAR)
    A_2 = random.randint(1,MAX_CLEAR)
    A_3 = random.randint(1,MAX_CLEAR)
    print(f"{A_1} {A_2} {A_3}")
    squares.append((A_1,A_2,A_3))

  for m in range(M):
    L,R_1,C_1,R_2,C_2 = pick()
    while R_1 == R_2 and C_1 == C_2:
      L,R_1,C_1,R_2,C_2 = pick()
  
    print(f"{R_1} {C_1} {R_2} {C_2} {L}")

