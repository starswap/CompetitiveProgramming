power = {"Shadow": 6,
        "Gale": 5,
        "Ranger": 4,
        "Anvil": 7,
        "Vexia": 3,
        "Guardian": 8,
        "Thunderheart": 6,
        "Frostwhisper": 2,
        "Voidclaw": 3,
        "Ironwood": 3,
        "Zenith": 4,
        "Seraphina": 1,
}

locs = []
for loc in range(3):
    locs.append((input().split()[1:], input().split()[1:]))
# print(locs)
total_power = [0, 0]
points = [0, 0]
for i in range(3):
    scores = [0, 0]
    for p in range(2):
        if len(locs[i][p]) >= 4 and "Thunderheart" in locs[i][p]:
            for j in range(len(locs[i][p])):
                if locs[i][p][j] == "Thunderheart":
                    locs[i][p][j] = power["Thunderheart"] * 2
        
        for j in range(len(locs[i][p])):
            if i == 1 and locs[i][p][j] == "Zenith":
                locs[i][p][j] = power["Zenith"] + 5
        
        num_seraphina = 0
        for j in range(len(locs[i][p])):
            if locs[i][p][j] == "Seraphina":
                num_seraphina += 1
        
        for j in range(len(locs[i][p])):
            if locs[i][p][j] in power:
                locs[i][p][j] = power[locs[i][p][j]] + num_seraphina + (-1 if locs[i][p][j] == "Seraphina" else 0)
            else:
                locs[i][p][j] += num_seraphina
        # print(sum(locs[i][p]))
        # print(locs[i][p])
        scores[p] = sum(locs[i][p])
        total_power[p] += sum(locs[i][p])
    
    if (scores[0] > scores[1]):
        points[0] += 1
    elif (scores[1] > scores[0]):
        points[1] += 1
    # print(points)


if points[0] > points[1]:
    print("Player 1")
elif points[0] == points[1]:
    if (total_power[0] > total_power[1]):
        print("Player 1")
    elif (total_power[1] > total_power[0]):
        print("Player 2")
    else:
        print("Tie")
else:
    print("Player 2")        
