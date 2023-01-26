T = int(input())
for t in range(T):
    N = int(input())
    nums = [*map(int, input().split())]

    evens = []
    odds = []
    for i,num in enumerate(nums):
        if (num % 2 == 0):
            evens.append(i)
        else:
            odds.append(i)
    
    if (len(evens) >= 2 and len(odds) >= 1):
        print("YES")
        print(" ".join(map(lambda x : str(x + 1), [evens[0], evens[1], odds[0]])))
    elif (len(odds) >= 3):
        print("YES")
        print(" ".join(map(lambda x : str(x + 1), odds[:3])))
    else:
        print("NO")
        

