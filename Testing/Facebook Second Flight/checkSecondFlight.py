TCs = int(input())

for t in range(1,TCs+1):
  N,M,Q = map(int,input().split())
  
  AL = [[] for i in range(N)]
  AM = [[0 for i in range(N)] for i in range(N)]
  
  for m in range(M):
    A,B,C = map(int,input().split())
    A -= 1
    B -= 1
    AL[A].append(B)
    AL[B].append(A)
    AM[A][B] = C
    AM[B][A] = C

  results = []
  for q in range(Q):
    X,Y = map(int,input().split())
    X -= 1
    Y -= 1
    cost = 2*AM[X][Y]
    for C in AL[X]:
      if AM[C][Y] > 0:
        cost += min(AM[X][C],AM[C][Y])
    results.append(cost)

  print(f"Case #{t}: {' '.join(map(str,results))}")
    
    
      

