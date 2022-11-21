import math
T = int(input())
for t in range(T):
    l,r,x = map(int,input().split())
    a,b = map(int,input().split())
    
    a2 = min(a,b)
    b2 = max(a,b)
    
    # print(a2,b2,l,r,x)
    if a == b:
        print(0)
    elif (a2 - l < x and r - a2 < x) or (b2 - l < x and r - b2 < x):
        print(-1)
    elif (abs(b-a) >= x):
        print(1)
    elif (a2 - l >= x and b2 - l >= x) or (r - b2 >= x and r - b2 >= x):
        print(2)
    else:
        print(3)
