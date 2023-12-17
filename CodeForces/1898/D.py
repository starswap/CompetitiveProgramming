T = int(input())
def f(a, b):
    return abs(a - b)

for t in range(T):
    N = int(input())
    A = [*map(int, input().split())]
    B = [*map(int, input().split())]
    intervals = [*map(lambda x, y: (min(x, y), max(x, y)), A, B)]
    rightestLeft = max(intervals,key=lambda x : x[0])
    leftestRight = min(intervals,key=lambda x : x[1])
    delta = -f(*rightestLeft)-f(*leftestRight) + f(rightestLeft[0], leftestRight[1]) + f(rightestLeft[1], leftestRight[0])
    originalScore = sum(map(lambda p : f(*p), intervals))
    print(delta + originalScore) 