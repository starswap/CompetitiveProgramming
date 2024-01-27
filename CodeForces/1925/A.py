T = int(input())
ALPHA = "abcdefghijklmnopqrstuvwxyz"
for i in range(T):
    N, K = map(int, input().split())
    print(ALPHA[:K] * N)
    