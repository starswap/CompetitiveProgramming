import os
import time
from itertools import groupby,chain,combinations

os.system("python generator.py")
start = time.time()
os.system("cat input.txt | ./a.out > output.txt")
end = time.time()
print("Delta Clock Time " + str(end-start) + " secs.")
reset = "\033[0m"

def rgb(r,g,b):
  return f"\033[38;2;{r};{g};{b}m"

with open("input.txt") as inp:
  with open("output.txt") as out:
    numCases = int(inp.readline().strip())
    fails = 0
    successes = 0
    for case in range(numCases):
      N,K = list(map(int,inp.readline().strip().split(" ")))
      numbers = list(map(int,inp.readline().strip().split(" ")))
      fail = False
      outLine = out.readline()
      if ("Impossible" in outLine):
        if (N < 25):
          sums = set([])
          
          for subset in chain(*[list(map(list,combinations(numbers,i))) for i in range(1,len(numbers)+1)]):
            summ = sum(subset)
            if summ in sums:
              fail = True
              break
            else:
              sums.add(summ)
          if (not(fail)):
            successes += 1
            #print(rgb(0,255,0) + "V")
          else:
            print(rgb(255,30,30) + "X - claimed impossible")
            fails += 1
        else:
          print(rgb(255,30,30) + "X - claimed impossible")
          
      else:
        thread1 = list(map(int,out.readline().strip().split(" ")))
        thread2 = list(map(int,out.readline().strip().split(" ")))

        sum1 = sum(map(lambda a : numbers[a-1],thread1))
        sum2 = sum(map(lambda a : numbers[a-1],thread2))
        if (sum1 != sum2):
          print(rgb(255,30,30) + "X - distinct sum")
          fail = True
          fails += 1
        else:
          if (len(numbers) - len(thread1) - len(thread2) <= K): #didn't throw more than K
            
            if (not(len(thread1+thread2) == len(set(thread1+thread2)))):
              #Used the same one several times.
              fail = True
              print(rgb(255,30,30) + "X - not a subset")
              fails += 1
            else:
              #print(rgb(0,255,0) + "V")
              successes += 1
          else:
            fail = True
            print(rgb(255,30,30)+ "X - threw more than K")

      #if (fail):
     #   print(reset,end="")
      #  print("\tCase was:")
       # print(f"\t{N} {K}")
       # print("\t"+' '.join(map(str,numbers)))

      #print(successes+fails)
     # if ((successes+fails) % (numCases/10) == 0):
      #  print(f"Done {successes+fails}")

    print(reset)
    print(f"From {numCases}:")
    print("\t"+rgb(0,255,0)+f"{successes} passes.")
    print("\t"+rgb(255,30,30)+f"{fails} fails.")

print(reset)


