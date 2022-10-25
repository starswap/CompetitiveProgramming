import random
import subprocess

TCs = 100
MAX_R = 10
MIN_R = 3
MAX_C = 10
MIN_C = 3
EDGE_DOOR_CHANCE = 0.2
CENTRE_CAR_CHANCE = 0.5
CENTRE_DOOR_CHANCE = 0.1

for t in range(TCs):
    output = ""
    r = random.randint(MIN_R,MAX_R)
    c = random.randint(MIN_C,MAX_C)
    output += (f"{r} {c}\n")

    cars = []
    row1 = ""
    for c1 in range(c):
        if (random.random() < EDGE_DOOR_CHANCE):
            row1 += "D"
        else:
            row1 += "#"
    output += (row1) + "\n"

    for row in range(r-2):
        currentRow = ""
        if (random.random() < EDGE_DOOR_CHANCE):
            currentRow += "D"
        else:
            currentRow += "#"
        
        for c1 in range(c-2):
            rand = random.random()
            if (rand < CENTRE_CAR_CHANCE):
                currentRow += "c"
                cars.append((row+2,c1+2))
            elif rand < CENTRE_CAR_CHANCE + CENTRE_DOOR_CHANCE:
                currentRow += "D"
            else:
                currentRow += "#"
        
        if (random.random() < EDGE_DOOR_CHANCE):
            currentRow += "D"
        else:
            currentRow += "#"
        
        output += (currentRow)+"\n"


    rowR = ""
    for c1 in range(c):
        if (random.random() < EDGE_DOOR_CHANCE):
            rowR += "D"
        else:
            rowR += "#"
    
    output += (rowR) + "\n"
 
    if len(cars) == 0:
        continue
    output += (" ".join(map(str,random.choice(cars)))) + "\n"

    dfsOut = str(subprocess.run("./DFS.exe",capture_output=True,text=True,input=output).stdout)
    bfsOut = str(subprocess.run("./BFS.exe",capture_output=True,text=True,input=output).stdout)
    if dfsOut != bfsOut:
        print("Dfs Output: " + dfsOut)
        print("Bfs Output: " + bfsOut)
        print("Input: " + output)
