import subprocess
import random
cmnd = r'''(type "C:\Users\marks\Documents\CP Problems\UVa\input.txt") | "C:\Users\marks\Documents\CP Problems\Kattis\abridgedreading2.exe"'''
print(cmnd)

MAX_N = 10

noChapters = random.randint(3,MAX_N)
noLinks = random.randint(1,noChapters-1)

rhs = set([])

with open(r'''C:\Users\marks\Documents\CP Problems\UVa\input.txt''',"w") as f:
        f.write(str(noChapters) + " " + str(noLinks) + "\n")
        for i in range(noChapters-1):
                f.write(str(random.randint(1,MAX_N)) + " ")
        f.write(str(random.randint(1,MAX_N)) + "\n")

        for j in range(noLinks):
                point2 = random.randint(3,noChapters)
                while point2 in rhs:
               #         print(point2)
                        point2 = random.randint(3,noChapters)
                #        print(rhs)
                
                point1 = random.randint(1,point2-1)        
                                      

                f.write(str(point1) + " " + str(point2)+"\n")
                rhs.add(point2)



try:
    output = subprocess.check_output(cmnd, stderr=subprocess.STDOUT,timeout=3,shell=True)
except subprocess.CalledProcessError as exc:
    print("Status : FAIL", exc.returncode, exc.output)
else:
    print("Output: \n{}\n".format(output))



