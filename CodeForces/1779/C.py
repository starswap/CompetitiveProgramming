from queue import PriorityQueue

T = int(input())
for t in range(T):
    n,m = map(int, input().split())
    currArry = list(map(int, input().split()))

    # pass back to front from e
    q = PriorityQueue()
    summ = 0
    flips = 0
    for i in range(m - 1, 0, -1):
        if (currArry[i] > 0):
            q.put(-currArry[i])
        summ += currArry[i]
        if (summ > 0):
            flips += 1
            summ += 2*q.get()


    q2 = PriorityQueue()
    summ = 0
    for i in range(m, len(currArry), 1):
        if (currArry[i] < 0):
            q2.put(currArry[i])
        summ += currArry[i]
        if (summ < 0):
            flips += 1
            summ += -2*q2.get()

    print(flips)

