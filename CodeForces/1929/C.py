T = int(input())
for t in range(T):
    K, X, A = map(int, input().split())
    J = K - 1
    D = [1]
    total_lost = 1
    poss = True
    for go in range(X - 1):
        # if total_lost >= A:
        #     poss = False
        new_stake = (total_lost // J) + 1
        D.append(new_stake)
        total_lost += new_stake
        # print(new_stake)
    rem = A - total_lost
    # print(total_lost)
    if rem <= 0:
        poss = False
    else: # stake the lot
        final = A - total_lost
        D.append(A - total_lost)
        
        if K * final - total_lost - final <= 0:
            poss = False

    # print(D)
    if poss:
        print("YES")
    else:
        print("NO")

    
    #d1 = 1
    # d2 = 1
