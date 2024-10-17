edges = []
N = 21
for r in range(N):
    for c in range(N):
        if c != N - 1:
            edges.append((r, c, r, c + 1))
        if r != N - 1:
            edges.append((r, c, r + 1, c))
print(len(edges))
for edge in edges:
    print(*edge)


