dx = [1,0,0,-1]
dy = [0,1,-1,0]

INF = 1000000000
MOD = 1000000007

fileName = input("Filename?")
TCNo = int(input("Number?"))
with open(fileName,"r") as f:  
  
  TCs = int(f.readline())
  for t in range(TCs):
      
    N,M = list(map(int,f.readline().split()))
    squares = []
    for i in range(N):
      squares.append(f.readline())
    
    # print(squares)
    queries = []
    for j in range(M):
      queries.append(f.readline())

    
    if t == TCNo-1:
      break

with open("oneTC","w") as g:
  g.write("1\n")
  g.write(f"{N} {M}\n")
  for sq in squares:
    g.write(sq)
  for q in queries:
    g.write(q)

    
    
    
    