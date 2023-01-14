T = int(input())
for t in range(T):
    n, x = map(int, input().split())

    powsOf2 = [1 << i for i in range(65)]

    lower_bound = n
    upper_bound = 5*10**18

    t = 1
    i = 0
    while t <= n or t <= x:
        # print(lower_bound)
        # print(upper_bound)
        # print(x & t)
        if x & t > 0:
            if n & t == 0:
                lower_bound = max(lower_bound,5*10**18 + 1)
                break
            else:
                # print ((1 << i+1) - 1))
                upper_bound = min(upper_bound,x | ((1 << i+1) - 1)) # x with last i + 1 bits as 1 
        else:
            if n & t > 0:
                lower_bound = max(lower_bound,(x & (~(1 << i))) + (1 << i + 1)) # x with last i +1 bits set as 0, and i + 2 set as 1

        i += 1
        t = t << 1

    # print(lower_bound)
    # print(upper_bound)
    if lower_bound > upper_bound:
        print(-1)
    else:
        print(lower_bound)



