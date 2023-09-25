T = int(input())
for t in range(T):
    R, C, A, B = map(int, input().split())
    print(f"Case #{t + 1}: ", end="")
    if R > C:
        print("YES")
    else:
        print("NO")