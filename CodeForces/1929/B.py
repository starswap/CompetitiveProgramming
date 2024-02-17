T = int(input())
for t in range(T):
    N, K = map(int, input().split())
    D = 4 * N - 2
    D_cap = 2 * (2 * N - 2) 

    if K <= D_cap:
        print((K + 1) // 2)
    else:
        K -= D_cap
        cells = D_cap // 2 + K
        print(cells) 

        # used N cells
        # got 2 *  N diags
    # first N will get 2 new diags every time







    # if K <= D // 2:
    # else:
    #     # done D // 2
    #     cells_used = ((D // 2) + 1) // 2
    #     rest = K - D // 2
    #     print(S + )

    #     print("Don't know")
    # # less than half the diagonals - just do 2 diagonals per node i.e. divide by 2
