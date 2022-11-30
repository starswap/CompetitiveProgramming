T = int(input())
prevP1 = 0
prevP2 = 0

whenFailed = -1

for t in range(1,T+1):
    p1,p2 = map(int,input().split("-"))
    if whenFailed != -1: # can't break as we need to consume rest of input, but don't need to process
        continue

    if ((p1 + p2) % 4 in (3,0) and (prevP1 + prevP2) % 4 in (1,2)) or ((p1 + p2) % 4 in (1,2) and (prevP1 + prevP2) % 4 in (0,3)):
        temp = prevP1
        prevP1 = prevP2
        prevP2 = temp

    if (p1,p2) == (11,11) or (p1 < prevP1 or p2 < prevP2) or ((p1,p2) != (prevP1,prevP2) and (prevP2 == 11 or prevP1 == 11)):
        whenFailed = t

    prevP1 = p1
    prevP2 = p2

if whenFailed > -1:
    print("error " + str(whenFailed))
else:
    print("ok")
