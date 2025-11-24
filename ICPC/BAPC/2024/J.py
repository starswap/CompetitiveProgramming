N = int(input())

A = 0
B = 0
fail = False
for n in range(N):
    a, b = map(int, input().split())
    if a < A or b < B:
        fail = True
    A = max(a, A)
    B = max(b, B)
print("yes" if not fail else "no")
