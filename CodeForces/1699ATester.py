import random
from subprocess import Popen, PIPE, STDOUT

for k in range(100):
        n = random.randint(1,10000000)
        print(n)

        cmd = r'''C:\Users\marks\Documents\CP Problems\CodeForces\1699A.exe'''
        print(cmd)

        p = Popen([cmd], stdout=PIPE, stdin=PIPE, stderr=STDOUT)    
        stdout = p.communicate(input=bytes("1\n" + str(n) + "\n",'ascii'))[0]


        array = list(map(int,stdout.decode().strip().split(" ")))
        print(array)
        
        a,b,c = tuple(array)
        
        print(a,b,c)
        print((a ^ b) + (b ^c) + (c ^ a))
