from collections import namedtuple
import copy
import random
import sys

random.seed(int(sys.argv[1]))

def pick(minMax):
  return random.randint(minMax.min,minMax.max)

def pickFloat(minMax):
  return minMax.min+random.random()*(minMax.max-minMax.min)

minMax = namedtuple("minMax","min max")
N = minMax(100,100) #100
LENGTH = minMax(1,20)
XY = minMax(-100,100)
Q = minMax(1,30)
AMT = minMax(1,10)
ALPHABET = "abcdefghijklmnopqrstuvwxyz-"


with open("input.txt","w") as f:
  n = pick(N)
  f.write(f"{n}\n")
  homeDone = False
  workDone = False
  pHome = 1/(n-1)
  pWork = 1/(n-1)
  names = []
  for i in range(n):
    if (random.random() < pHome) and homeDone == False:
      name = "home"
      homeDone = True
    else:
      pHome += 1/(n-1)
      if (random.random() < pWork) and workDone == False:
        name = "work"
        workDone = True
      else:
        pWork += 1/(n-1)
        name = ''.join([random.choice(ALPHABET) for i in range(pick(LENGTH))])
        while (name in names):
          name = ''.join([random.choice(ALPHABET) for i in range(pick(LENGTH))])
    names.append(name)
    x = pickFloat(XY)
    y = pickFloat(XY)
    f.write("%s %.5f %.5f\n" % (name,x,y))
    
  q = pick(Q)
  AMT = minMax(1,min(10,n-2))
  names.remove("home")
  names.remove("work")
  
  for i in range(q):  
    amt = pick(AMT)
    thisTime = []
    names2 = copy.deepcopy(names)
    for j in range(amt):
      currName = random.choice(names2)
      names2.remove(currName)
      thisTime.append(currName)
    f.write(f"{' '.join(thisTime)}\n")
