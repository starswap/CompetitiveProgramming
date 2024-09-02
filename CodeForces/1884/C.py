import copy
T = int(input())
for t in range(T):
    N, M = map(int, input().split())
    segs = []
    for i in range(N):
        l, r = map(int, input().split())
        segs.append((l-1, r-1))
    segs.sort()
    segs2 = copy.deepcopy(segs)
    segs2.sort(key=lambda x : x[1])

    segsIn = set([])
    entry_ptr = 0
    exit_ptr = 0
    segments = [0 for i in range(M)]
    # print(segs)
    # print(segs2)
    for i in range(M):
        while entry_ptr < N and segs[entry_ptr][0] <= i:
            segsIn.add(segs[entry_ptr])
            entry_ptr += 1
        segments[i] = len(segsIn)
        # print(segsIn)
        while exit_ptr < N and segs2[exit_ptr][1] <= i:
            segsIn.remove(segs2[exit_ptr])
            exit_ptr += 1
    
    # print(segments)

    segsIn = set([])
    all_segs = set(segs)
    num_segs = 0
    min_ele = min(segments)
    entry_ptr = 0
    exit_ptr = 0
    for i in range(M):
        while entry_ptr < N and segs[entry_ptr][0] <= i:

            segsIn.add(segs[entry_ptr])
            entry_ptr += 1
            num_segs += 1
        if num_segs == min_ele:
            # print(segsIn)
            for item in segsIn:
                all_segs.remove(item)
            segsIn = set([])
        segments[i] = len(segsIn)
        while exit_ptr < N and segs2[exit_ptr][1] <= i:
            if segs2[exit_ptr] in segsIn:
                segsIn.remove(segs2[exit_ptr])
                num_segs -= 1
            exit_ptr += 1

    segsIn = set([])
    segs = list(all_segs)
    segs2 = list(all_segs)
    segs.sort()
    segs2.sort(key=lambda x : x[1])
    entry_ptr = 0
    exit_ptr = 0
    for i in range(M):
        while entry_ptr < len(segs) and segs[entry_ptr][0] <= i:
            # print(entry_ptr)
            # print(N)
            # print(segs)
            segsIn.add(segs[entry_ptr])
            entry_ptr += 1
        segments[i] = len(segsIn)
        # print(segsIn)
        while exit_ptr< len(segs)and segs2[exit_ptr][1] <= i:
            segsIn.remove(segs2[exit_ptr])
            exit_ptr += 1
    
    print(max(segments) - min(segments))
        
