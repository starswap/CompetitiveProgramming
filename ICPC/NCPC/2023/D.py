dice = [[*map(int, input().split())]for i in range(3)]
done = False
for i in range(3):
    ok = True
    for j in range(3):
        prob = 0
        if i == j:
            continue
        x = 0
        y = 0
        for outcomeJ in dice[i]:
            for outcomeH in dice[j]:
                if outcomeJ > outcomeH:
                    x += 1 / 36
                elif outcomeJ == outcomeH:
                    y += 1 / 36
        if y != 1:
            prob = x / (1 - y)

        if prob < 1/2:
            ok = False
    if ok:
        done = True
        print(i+1)
        break
if not(done):
    print("No dice")