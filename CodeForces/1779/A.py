T = int(input())
for t in range(T):
    l = int(input())
    st = input()
    firstR = -1
    lastL = -1
    for i,lett in enumerate(st):
        if (firstR == -1 and lett == 'R'):
            firstR = i
        elif lett == 'L':
            lastL = i
    if (lastL == -1 or firstR == -1):
        print(-1)
    elif lastL > firstR:
        print(0)
    else:
        print(lastL+1)