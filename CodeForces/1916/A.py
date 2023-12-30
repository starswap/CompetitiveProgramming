T = int(input())
for t in range(T):
    N, K = map(int, input().split())
    B = map(int, input().split())
    b_prod = 1
    for b in B:
        b_prod *= b
    if 2023 % b_prod == 0:
        ans = [2023 // b_prod] + [1] * (K - 1)
        print("YES")
        print(" ".join(map(str, ans)))
    else:
        print("NO")