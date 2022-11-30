T = int(input())
for t in range(T):
    n = int(input())
    if n == 1:
        print(1)
    elif n % 2 == 1:
        nums = ["1"]*n
        print(' '.join(nums))
    else:
        nums = ["2"]*(n-2)
        print(' '.join(nums) + " 1" + " 3")
