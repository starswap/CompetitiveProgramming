N = int(input())
A = [*map(int, input().split())]
Q = int(input())

INF = 1000000000000

def check(B, s, e):
    mins = []
    A = []
    for item in B[s:e+1]:
        if not A or A[-1] != item:
            A.append(item)
    for i in range(0, len(A)):
        left = INF if i == 0 else A[i - 1]
        right = INF if i == len(A) - 1 else A[i + 1]
        if left > A[i] and right > A[i]:
            mins.append(A[i])
    increasing = True
    # print(mins)
    for i in range(len(mins) - 1):
        if mins[i + 1] <= mins[i]:
            increasing = False
    return increasing

for q in range(Q):
    line = input().split()
    if line[0] == "check":
        print("YES" if check(A, int(line[1]) - 1, int(line[2]) - 1) else "NO")
    elif line[0] == "update":
        s, f, d = map(int, line[1:])
        s -= 1
        f -= 1
        for i in range(s, f + 1):
            A[i] += d
