string = input()
impossible = False

opposite = {"L":"R", "R":"L", "U":"D", "D":"U"}
deltas = {"L":(1, 0), "R":(-1, 0), "U":(0, -1), "D":(0, 1)}

for i in range(len(string) - 1):
    impossible = impossible or string[i] == string[i + 1]

impossible = impossible or (len(string) >= 3 and string[-2] == opposite[string[-1]] and string[-3] == opposite[string[-2]])

if impossible:
    print("impossible")
else:
    reversedCommands = ""
    for i in range(len(string)-1, -1, -1):
        if i == len(string) - 1 or string[i] != opposite[string[i + 1]]:
            reversedCommands = reversedCommands + opposite[string[i]]

    ballPos = (0, 0)
    minX = 0
    maxX = 0
    minY = 0
    maxY = 0
    delta = 5

    spots = []

    for i, cmd in enumerate(reversedCommands):
        if cmd == "U":
            ballPos = (ballPos[0], maxY + delta)
        elif cmd == "D":
            ballPos = (ballPos[0], minY - delta)
        elif cmd == "L":
            ballPos = (minX - delta, ballPos[1])
        elif cmd == "R":
            ballPos = (maxX + delta, ballPos[1])

        if i != len(reversedCommands) - 1:
            offset = deltas[reversedCommands[i + 1]]
            spots.append((ballPos[0] + offset[0], ballPos[1] + offset[1])) 
        
        minX = min(minX, ballPos[0])
        maxX = max(maxX, ballPos[0])
        minY = min(minY, ballPos[1])
        maxY = max(maxY, ballPos[1])

    print(f"{ballPos[0]} {ballPos[1]}")
    print(len(spots))

    for (x, y) in spots:
        print(f"{x} {y}")
