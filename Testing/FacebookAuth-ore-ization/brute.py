dx = [1,0,0,-1]
dy = [0,1,-1,0]

INF = 1000000000
MOD = 1000000007

def solve(R_1,C_1,R_2,C_2,L,squares,N):
  visited = set([])
  
  def solveInternals(R_1,C_1):
    nonlocal visited
  #  print("Current " + str((R_1,C_1)) + "; Target " + str((R_2,C_2)))
    visited.add((R_1,C_1))
    if R_1 == R_2 and C_1 == C_2:
   #   print("Base")
      visited.remove((R_1,C_1))
      return 0
    else:
      best = INF
      for i in range(4):
        newR = R_1+dx[i]
        newC = C_1+dy[i]
        if (newR < N and newR >= 0 and newC < 3 and newC >= 0) and (L >= squares[newR][newC]) and not((newR,newC) in visited):
          best = min(best,1+solveInternals(newR,newC))

      visited.remove((R_1,C_1))
      return best
      
  # if ((a := solveInternals(R_1,C_1)) == INF):
  #   print("fail")
  return solveInternals(R_1,C_1)


TCs = int(input())
for t in range(TCs):
  N,M = list(map(int,input().split()))
  squares = [[0,0,0] for i in range(N)]
  for i in range(N):
    squares[i] = list(map(int,input().split()))
  
  # print(squares)
  res = 1
  for j in range(M):
    R_1,C_1,R_2,C_2,L = list(map(int,input().split()))
    R_1 -= 1
    C_1 -= 1
    R_2 -= 1
    C_2 -= 1
    ans = solve(R_1,C_1,R_2,C_2,L,squares,N)
    if ans != INF:
      res *= ans
      res %= MOD
    
  print(f"Case #{t+1}: {res}")
  
    
    