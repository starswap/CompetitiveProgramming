T = int(input())
for t in range(T):
    N, M, K = map(int, input().split())
    targlen = (N - 1 + M - 1)
    wasteage = K - targlen

    if wasteage < 0 or wasteage % 2 == 1: # not enough or odd wastage
        print("NO")
    else:
        print("YES")
        vertlines = N - 1
        colours = ["R", "B"]


        curr = 0
        for i in range(M - 1):
            print(colours[curr], end = " ")
            curr += 1
            curr %= 2
        print()
        for n in range(N - 2): # horiz
            print(" ".join(["R"]*(M - 1)))
        curr = vertlines % 2
        for i in range(M - 1):
            print(colours[curr], end = " ")
            curr += 1
            curr %= 2
        print()
    
        curr = 1
        curr_far = 1 - (M % 2)
        for m in range(N-1): # vert
            print(colours[curr], end = " ")
            print(" ".join(["B"]*(M - 2)), end=" ")
            print(colours[curr_far])
            curr_far += 1
            curr_far %= 2
            if m > 0:
                curr += 1
                curr %= 2