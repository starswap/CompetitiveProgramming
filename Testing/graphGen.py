from collections import namedtuple
import random
import math
import sys

def choose(n,r):
  return math.factorial(n)/(math.factorial(r)*math.factorial(n-r))

def pick(minMax):
  return random.randint(minMax.min,minMax.max)
  
minMax = namedtuple("minMax", "min max")

EXTRA_EDGE_CAP = 10000 #large complete graphs are slow to generate; cap the number of extra edges.
TC = 1
N = minMax(20,20) #20 
COST = minMax(1,3600)

TREE = False
WEIGHTED = False
print("a")
if len(sys.argv) > 1:
  args = sys.argv[1:]
  print(args)
  try:
    TC = int(args[0])
    N = minMax(int(args[1]),int(args[2]))
    COST = minMax(int(args[3]),int(args[4]))
    if args[5] == "False":
      TREE = False
    else:
      TREE = True

    if args[6] == "False":
      WEIGHTED = False
    else:
      WEIGHTED = True
      
  except IndexError:
    print("Incorrect arguments")
    sys.exit()
  
else:
  print("No arguments, assuming constant defaults.")
  print("Argument format: python graphGen.py <TC> <minN> <maxN> <minCost> <maxCost> <tree> <weighted>")


with open("inputGraph.txt","w") as f:
  f.write(f"{TC}\n")
  for case in range(TC):
    n = pick(N)

    #Starting at 1
    connected = [set() for i in range(n+1)]
    if WEIGHTED:
      edges = [(1,2,pick(COST))] # seed
      connected[1].add(2)
      connected[2].add(1)
    else:
      edges = [(1,2)] # seed
      connected[1].add(2)
      connected[2].add(1)
    
    for i in range(3,n+1):
      other = random.randint(1,i-1)
      if WEIGHTED:
        cost = pick(COST)
        edges.append((i,other,cost)) 
      else:
        edges.append((i,other))
      connected[i].add(other)
      connected[other].add(i)

    if not(TREE):
      if choose(n,2)-n+1 > 2:
        Mextra = minMax(2,choose(n,2)-n+1)
        extra = pick(Mextra)
        extra = min(extra,EXTRA_EDGE_CAP) 
      else:
        extra = 0
      m = n-1 + extra
    
      for i in range(extra):
        u = random.randint(1,n)
        v = random.randint(1,n)
        while v in connected[u] or u == v:
          u = random.randint(1,n)
          v = random.randint(1,n)
        if WEIGHTED:
          cost = pick(COST)
          edges.append((u,v,cost))
        else:
          edges.append((u,v))
  
        connected[u].add(v)
        connected[v].add(u)

    if not(TREE):
      f.write(f"{n} {m}\n")
    else:
      f.write(f"{n}\n")
      
    for edge in edges:
      f.write(f"{' '.join(map(str,edge))}\n")
  