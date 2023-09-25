T = int(input())
for t in range(T):
    S, D, K = map(int, input().split())
    patties = S + 2 * D
    breads = 2 * (S + D)
    print(f"Case #{t + 1}: ", end="")
    if patties >= K and breads >= K + 1:
        print("YES")
    else:
        print("NO")