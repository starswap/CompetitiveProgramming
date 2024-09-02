def solve(n):
    if n % 2 == 1:
        return -1
    else:
        return f"{1} {n//2}"

T = int(input())
for t in range(T):
    N = int(input())
    print(solve(N))
