N = int(input())
numbers = [*map(int, input().split())]
best_d = -1
best_t = 100
for i in range(N - 2):
    max_t = max(numbers[i], numbers[i + 2])

    if max_t < best_t:
        best_d = i + 1
        best_t = max_t
print(f"{best_d} {best_t}")

