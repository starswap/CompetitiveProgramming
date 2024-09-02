T = int(input())
for t in range(T):
    N = int(input())
    nums = [*map(int, input().split())]
    un = set(nums)

    if 0 not in un:
        print(2)
        print("1 1")
        print(f"2 {N}")
    else:
        contained = set([])
        startP = 0
        done = False
        for i in range(N): # mex
            if i in un:
                while not (i in contained):
                    contained.add(nums[startP])
                    startP += 1
            else:
                # print(contained)
                for item in nums[startP:]:
                    if item in contained:
                        contained.remove(item)
                
                fail = False
                for j in range(0, i):
                    if j in contained:
                        fail = True
                
                if fail:
                    print(-1)
                else:
                    print(2)
                    print(f"{1} {startP}")
                    print(f"{startP + 1} {N}")
                done = True
                break
        if not done:
            print(-1)