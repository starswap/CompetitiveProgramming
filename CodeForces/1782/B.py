T = int(input())
for t in range(T):
    N = int(input())
    counts = list(map(lambda x :  int(x), input().split()))
    counts.sort(key=lambda x : -x)

    possWays = 1
    start = 0
    while start < N:
        while start < N - 1 and counts[start + 1] == counts[start]:
            start += 1
        #start points to the last person that is not going
        numGoing = N - 1 - start

        if numGoing < counts[start] and (start == N - 1 or numGoing > counts[start + 1]): # ensure that: people not going don't want to go and people going want to go
            possWays += 1
        
        start += 1
    
    print(possWays)

    