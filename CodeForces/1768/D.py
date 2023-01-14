T = int(input())
for t in range(T):
    n = int(input())
    nums = list(map(int, input().split()))
    unvisited = set(range(1,n+1))
    
    totalReq = n
    curr = 1
    minDone = 1
    groups = [[]]
    while len(unvisited):
        # print(curr)
        if curr in unvisited: 
            groups[-1].append(curr)
            unvisited.remove(curr)
        else:
            totalReq -= 1
            curr = minDone
            groups.append([])

        while not(minDone in unvisited) and len(unvisited):
            minDone += 1
        
        curr = nums[curr-1]
    

    sort = totalReq - 1
    if (sort == 0):
        print(1)
    else:
        oneLess = False
        for group in groups:
            sortt = sorted(group)
            for i in range(len(sortt)-1):
                if (abs(sortt[i] - sortt[i+1]) == 1):
                    oneLess = True

        if oneLess:
            print(sort-1)
        else:
            print(sort+1)
    