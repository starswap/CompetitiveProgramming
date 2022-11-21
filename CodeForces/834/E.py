def solve(power,idx,green,blue):
    # print(f"solve({power},{idx},{green},{blue})")
    # print(astroPowers)
    while idx < len(astroPowers) and astroPowers[idx] < power:
        # print("eat " + str(idx))
        power += astroPowers[idx]//2
        idx += 1
    
    if (idx == len(astroPowers) or green == 0 and blue == 0):
        return idx
    else:
        if green >= 1 and blue >= 1:
            return max(solve(power*2,idx,green-1,blue),solve(power*3,idx,green,blue-1)) 
        elif green >= 1:
            return solve(power*2,idx,green-1,blue)
        else:
            return solve(power*3,idx,green,blue-1)

T = int(input())
for t in range(T):
    n,h = map(int,input().split())
    astroPowers = sorted([*map(int,input().split())])
    print(solve(h,0,2,1))