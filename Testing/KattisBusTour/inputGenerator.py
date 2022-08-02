from collections import namedtuple
import random
import math

def choose(n,r):
  return math.factorial(n)/(math.factorial(r)*math.factorial(n-r))

def pick(minMax):
  return random.randint(minMax.min,minMax.max)
  
minMax = namedtuple("minMax", "min max")


TC = 5
N = minMax(3,20) #20 
COST = minMax(1,3600)

with open("input.txt","w") as f:
  for case in range(TC):
    n = pick(N)

    assignedNodes = set()
    edges = []
    connected = [set() for i in range(n)]
    nodes = set(range(0,n))
  
    #Build Tree
    while len(nodes) > 0:
      u = random.choice(list(nodes))
      if (len(assignedNodes) > 0):
        v = random.choice(list(assignedNodes))
        cost = pick(COST)
        edges.append((u,v,cost))
        connected[u].add(v)
        connected[v].add(u)
      assignedNodes.add(u)
      nodes.remove(u)
    
    if choose(n,2)-n+1 > 2:
      Mextra = minMax(2,choose(n,2)-n+1)
      extra = pick(Mextra)
    else:
      extra = 0
    m = n-1 + extra
  
    for i in range(extra):
      u = random.randint(0,n-1)
      v = random.randint(0,n-1)
      while v in connected[u] or u == v:
        u = random.randint(0,n-1)
        v = random.randint(0,n-1)
      cost = pick(COST)
      edges.append((u,v,cost))
      connected[u].add(v)
      connected[v].add(u)
  
    f.write(f"{n} {m}\n")
    for (u,v,cost) in edges:
      f.write(f"{u} {v} {cost}\n")
  