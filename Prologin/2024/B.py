K = int(input())
N = int(input())
tailles = [*map(int, input().split())]

for i in range(K):
    sous_tailles = [tailles[j] for j in range(i, N, K)]
    sous_tailles.sort()
    c = 0
    for j in range(i, N, K):
        tailles[j] = sous_tailles[c]
        c += 1

ordonne = sorted(tailles)
if ordonne == tailles:
    print("OUI")
else:
    print("NON")
