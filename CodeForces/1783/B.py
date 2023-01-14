def printArray(arr):
    for line in arr:
        print(" ".join(map(str,line)))

T = int(input())
for t in range(T):
    n = int(input())

    dr = [0,1,0,-1]
    dc = [1,0,-1,0]
    i = 0
    count = 0
    r = 0
    c = 0
    arr = [[0]*n for i in range(n)]

    while count != n*n:
        if (count % 2 == 0):
            arr[r][c] = 1 + count//2
        else:
            arr[r][c] = n*n - count//2
        
        if (r + dr[i]) >= n or r + dr[i] < 0 or c + dc[i] >= n or c + dc[i] < 0 or arr[r+dr[i]][c+dc[i]] != 0:
            i += 1
            i %= 4

        r += dr[i]
        c += dc[i]

        count += 1
    printArray(arr)