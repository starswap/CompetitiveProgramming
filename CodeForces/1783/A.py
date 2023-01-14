T = int(input())
for t in range(T):
    n = int(input())
    nums = list(map(int, input().split()))
    
    if (len(set(nums)) == 1):
        print("NO")
    else:
        print("YES")
        array = sorted(nums, key=lambda x : -x)
        temp = array[-1]
        array[-1] = array[1]
        array[1] = temp
        print(" ".join(map(str,array)))