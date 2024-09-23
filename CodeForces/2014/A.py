T = int(input())
for t in range(T):
    N, K = map(int, input().split())
    A = map(int, input().split())
    gold = 0
    given = 0
    for item in A:
        if item >= K:
            gold += item
        elif gold > 0 and item == 0:
            given += 1
            gold -= 1
    print(given)