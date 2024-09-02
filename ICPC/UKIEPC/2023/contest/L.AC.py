H1, D1, T1 = map(int, input().split())
H2, D2, T2 = map(int, input().split())

if H1 % D2 == 0:
    turnsToKill1 = H1 / D2
else:
    turnsToKill1 = H1 // D2 + 1


if H2 % D1 == 0:
    turnsToKill2 = H2 / D1
else:
    turnsToKill2 = H2 // D1 + 1

timeToKill1 = (turnsToKill1 - 1) * T2
timeToKill2 = (turnsToKill2 - 1) * T1

if timeToKill1 == timeToKill2:
    print("draw")
elif timeToKill1 < timeToKill2:
    print("player two")
else:
    print("player one")