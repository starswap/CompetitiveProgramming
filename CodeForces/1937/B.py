T = int(input())
for t in range(T):
    N = int(input())
    a1 = input()
    a2 = input()

    res = [a1[0]]
    snd = -1
    same = 0
    sameAns = 0
    for i in range(0, N):
        # print(same)

        if snd == -1 and (i == N - 1 or (a2[i] == "0" and a1[i + 1] == "1")):
            snd = i
            sameAns = same

        if i != N - 1:
            if a2[i] == a1[i + 1]:
                same += 1
            else:
                same = 0

        if snd == -1:
            res.append(a1[i + 1])
        else:
            res.append(a2[i])
    print("".join(res))
    print(sameAns + 1)