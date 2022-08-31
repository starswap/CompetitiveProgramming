import random
MAX = 3000
TCs = 10
with open("input2.txt","w") as f:
    f.write(f"{TCs}\n")
    for t in range(TCs):
      print(t)
      f.write(f"{MAX} {MAX}\n")
      for i in range(MAX):
          for j in range(MAX):
              f.write(random.choice([".",".",".",".",".","#","^","^","^"]))
          f.write("\n")
          
                
        
