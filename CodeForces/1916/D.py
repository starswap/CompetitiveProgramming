T = int(input())
for t in range(T):
    N = int(input())
    if N == 1:
        print(1)
    else:
        orders = [[1, 6, 9], [9, 6, 1]]
        ans = []
        for order in orders:
            for sep in range((N - 3) // 2 + 1):
                num = str(order[0]) + "0" * sep + str(order[1]) + "0" * sep + str(order[2])
                num += "0" * (N - len(num))
                ans.append(num)
        ans.append("196" + "0" * (N - 3))
        print(len(ans))
        # print("\n".join(ans))