MAX = 1000001
ans = [0 for _ in range(MAX)]
x = 1
for i in range(1, MAX):
    x *= i
    while x % 10 == 0:
        x //= 10
    x %= 10000000
    ans[i] = x % 10

N = int(input())
while N != 0:
    print(ans[N])
    N = int(input())
