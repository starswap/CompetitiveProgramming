from collections import Counter
T = int(input())
for t in range(T):
    N, K = map(int, input().split())
    string = input()
    counts = Counter(string)
    odds = 0
    for cnt in counts:
        if counts[cnt] % 2 == 1:
            odds += 1
    if K >= odds - 1:
        print("YES")
    else:
        print("NO")