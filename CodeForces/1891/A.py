T = int(input())
for t in range(T):
    N = int(input())
    nums = map(int, input().split())

    max_this_segment = 0
    fail = False
    next_po_2 = 1
    for i, item in enumerate(nums):
        if max_this_segment > item:
            fail = True
            break
        else:
            max_this_segment = max(max_this_segment, item)
        if i + 1 == next_po_2:
            max_this_segment = 0
            next_po_2 *= 2
    if fail:
        print("NO")
    else:
        print("YES")