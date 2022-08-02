import itertools
import math

n = int(input())
places = {}
for i in range(n):
  line = input().split()  
  places[line[0]] = {"x":float(line[1]),"y":float(line[2])}

def getScore(place1,place2):
  return math.sqrt((places[place1]["x"]-places[place2]["x"])**2 + (places[place1]["y"]-places[place2]["y"])**2)
  
try:
  while True:
    placesToGo = input().split()
    bestScore = 1000000000
    bestOrder = []
    for perm in itertools.permutations(placesToGo):
      perm2 = ["work"] + list(perm) + ["home"]
      score = 0
      for i in range(len(perm2)-1):
        score += getScore(perm2[i],perm2[i+1])

      if score < bestScore:
        bestScore = score
        bestOrder = list(perm)

    print(' '.join(bestOrder))
      
except EOFError:
  pass
  