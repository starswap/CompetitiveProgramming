N = int(input())
K = N // 2
print(K)
ans = []
for i in range(K):
    if i == K - 1:
        ans.append(2 + N % 2)
    else:
        ans.append(2)
print(*ans)
