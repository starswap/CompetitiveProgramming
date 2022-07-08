import random
from subprocess import Popen, PIPE, STDOUT

for k in range(100):

        n = random.choice(range(2,52,2))
        m = random.choice(range(2,52,2))
        print(n,m)
        #n = 2
        #m = 2

        cmd = r'''C:\Users\marks\Documents\CP Problems\CodeForces\1699B.exe'''
        print(cmd)

        p = Popen([cmd], stdout=PIPE, stdin=PIPE, stderr=STDOUT)    
        stdout = p.communicate(input=bytes("1\n" + str(n) + " " + str(m) + "\n",'ascii'))[0]


        array = list(map(lambda a : a.strip().split(" "),stdout.decode().split("\n")))[:-1]
        #print(array)

        ok = len(array) == n and len(array[0]) == m

        for i in range(len(array)):
                for j in range(len(array[0])):
                        total = 0
                        if i > 0:
                                total += int(array[i][j] != array[i-1][j])
                        if i < len(array) - 1:
                                total += int(array[i][j] != array[i+1][j])
                        if j > 0:
                                total += int(array[i][j] != array[i][j-1])
                        if j < len(array[0]) - 1:
                                total += int(array[i][j] != array[i][j+1])
                        if total != 2:
                                print(i,j)
                                ok = False

        print(ok)



