T = int(input())
for t in range(T):
    N = int(input())
    A = map(int, input().split())
    product = 1
    for item in A:
        product *= item
    if product <= 0:
        print(0)
    else:
        print(1)
        print(1, 0)