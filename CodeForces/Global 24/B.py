T = int(input())
for t in range(T):
    n = int(input())
    nums = [*map(int, input().split())]
    b = max(nums)
    
    while len(nums) > 1:
        m = min(nums)
        nums = [*filter(lambda x : x != 0, [m] + list(map(lambda x : x % m, nums)))]
 #       print(nums)
    # m = min(nums)
    print(b // m)


    