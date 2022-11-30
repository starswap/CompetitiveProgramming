import random
import time
import os

for i in range(10000):

    with open("tc.txt","w") as f:
        f.write("1\n")
        f.write("200000\n")
        nums = [random.randint(1,200000) for i in range(200000)] #+ [1 for i in range(100000)]
        f.write(" ".join(map(str,nums))+"\n")
    print(nums[-1])

    start = time.time()
    os.system("type tc.txt | a.exe")
    end = time.time()
    print(end-start)
    if (end-start > 1):
        break


