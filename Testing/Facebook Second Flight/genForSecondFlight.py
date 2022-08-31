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
TC = 10
MIN_N = 8000
MAX_N = 8000
MIN_COST = 1
MAX_COST = 1*10**9
TREE = False
WEIGHTED = True
MIN_Q = 800
MAX_Q = 800

Q = minMax(MIN_Q,MAX_Q)
N = minMax(MIN_N,MAX_N) #20 
COST = minMax(MIN_COST,MAX_COST)

with open("inputGraph.txt","w") as f:
  f.write(f"{TC}\n")
  for case in range(TC):
    n = pick(N)
    q = pick(Q)


    #Starting at 1
    connected = [set() for i in range(n+1)]
    connectedList = [[] for i in range(n+1)]
    if WEIGHTED:
      edges = [(1,2,pick(COST))] # seed
      connected[1].add(2)
      connected[2].add(1)
      connectedList[1].append(2)
      connectedList[2].append(1)
    else:
      edges = [(1,2)] # seed
      connected[1].add(2)
      connected[2].add(1)
      connectedList[1].append(2)
      connectedList[2].append(1)
    
    for i in range(3,n+1):
      other = random.randint(1,i-1)
      if WEIGHTED:
        cost = pick(COST)
        edges.append((i,other,cost)) 
      else:
        edges.append((i,other))
      connected[i].add(other)
      connected[other].add(i)
      connectedList[i].append(other)
      connectedList[other].append(i)      

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
        connectedList[u].append(v)
        connectedList[v].append(u)        

    if not(TREE):
      f.write(f"{n} {m} {q}\n")
    else:
      f.write(f"{n}\n")
      
    for edge in edges:
      f.write(f"{' '.join(map(str,edge))}\n")


    queries = []
    for i in range(q):
      A = random.randint(1,n)
      B = random.choice(connectedList[A])
      queries.append((A,B))
      
    for query in queries:
      f.write(f"{' '.join(map(str,query))}\n")

    
      
      


    
  