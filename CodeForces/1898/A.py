T = int(input())
for t in range(T):
    N, K = map(int, input().split())
    string = input()
    Bs = string.count("B")
    # print(Bs)
    if Bs == K:
        print(0)
    elif Bs < K:
        As_needed = K - Bs
        As_seen = 0
        for i in range(N):
            if string[i] == "A":
                As_seen += 1
            if As_seen == As_needed:
                print(1)
                print(f"{i + 1} B")
                break
    else: # too many bs already
        Bs_needed = Bs - K
        Bs_seen = 0
        for i in range(N):
            if string[i] == "B":
                Bs_seen += 1
            if Bs_seen == Bs_needed:
                print(1)
                print(f"{i + 1} A")
                break
