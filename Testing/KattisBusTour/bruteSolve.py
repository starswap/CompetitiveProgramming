import itertools
from math import floor

def getCost(route,costs):
  cost = 0
  for i in range(len(route)-1):
    cost += costs[route[i]][route[i+1]]
    
  return cost

try:
  caseNo = 1
  while True:
    n,m = map(int,input().split())
    costs = [[100000000 for i in range(n)] for i in range(n)]
    for i in range(m):
      u,v,cost = map(int,input().split())
      costs[u][v] = cost
      costs[v][u] = cost

    for k in range(n):
      for i in range(n):
        for j in range(n):
          costs[i][j] = min(costs[i][j],costs[i][k]+costs[k][j])
   # print(costs)
    best = 100000000
    bestRoute = []
    for perm1 in itertools.permutations(list(range(1,n-1))):
      for perm2 in itertools.permutations(list(range(1,n-1))):
        if set(perm1[:floor((n-2)/2)]) == set(perm2[:floor((n-2)/2)]):
          route = [0] + list(perm1) + [n-1] + list(perm2) + [0]
          cost = getCost(route,costs)
          if (cost < best):
            best = cost
            bestRoute = route
    #        print(bestRoute)
   #         print(perm1)
 ##           print(perm2)
         #if (cost == 200):
        #  print(route)
          
    print(f"Case {caseNo}: {best}")
#    print(bestRoute)
    caseNo += 1
          
except EOFError:
  pass
