import math
T = int(input())
for t in range(T):
    
    L = int(input())
    if (L == 2):
        print("YES")
        print("1 1")
    elif (L == 3):
        print("NO")
    else:
        p = math.ceil(L / 2) - 1
        q = math.floor(L / 2) - 1
        x = q
        y = -p
        print("YES")
        nums = []
        for i in range(L):
            nums.append(x if i % 2 == 0 else y)
        print(" ".join(map(str,nums)))
     