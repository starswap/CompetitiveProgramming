T = int(input())
for t in range(T):
    mxX = -1000000000000
    minX = 1000000000000
    mxY = -1000000000000
    minY = 1000000000000
    for i in range(4):
        x, y = map(int, input().split())
        mxX = max(mxX, x)
        minX = min(minX, x)
        minY = min(minY, y)
        mxY = max(mxY, y)
    print((mxY - minY) * (mxX - minX))