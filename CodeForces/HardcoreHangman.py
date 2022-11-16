import sys

ALPHA = "abcdefghijklmnopqrstuvwxyz"

print("? " + ALPHA)
sys.stdout.flush()

letterBounds = [(0,25) for posn in input().split(" ")[1:]]
queryRanges = [(0,25)]

for i in range(5):
    queryRangesPrime = []
    for (s,e) in queryRanges:
        queryRangesPrime.append((s,(s+e)//2))
    
    #ask query
    toAsk = ""
    for (s,e) in queryRangesPrime:
        for t in range(s,e+1):
            toAsk += ALPHA[t]
    
    print("? " + toAsk)
    sys.stdout.flush()
    
    line = input()
    returnedPosns = []
    if line[0] != "0":
        returnedPosns = list(map(lambda a : int(a)-1,line.split(" ")))[1:]
    # else:
    #    print("ahop")

    j = 0
    for i,(s,e) in enumerate(letterBounds):
        if j < len(returnedPosns) and i == returnedPosns[j]: # i was returned 
            letterBounds[i] = (s,(s+e)//2)
            j += 1
        else:
            letterBounds[i] = ((s+e)//2+1,e)

    for (s,e) in queryRanges:
        queryRangesPrime.append(((s+e)//2+1,e))
    queryRanges = queryRangesPrime

print("! " + ''.join(map(lambda t: ALPHA[t[0]],letterBounds)))
sys.stdout.flush()
