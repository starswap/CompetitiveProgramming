N, M, K = map(int, input().split())

def solve_card(taps):
    points_for_card = 0
    for i in range(0, len(taps), 2):
        points_for_card += solve_journey(taps[i:i+2])
    return points_for_card

def solve_journey(taps):
    if len(taps) == 0 or taps[0] == taps[-1]:
        return 100
    else:
        return abs(taps[0] - taps[-1])

cards = [[] for i in range(M)]
for i in range(K):
    p, c = map(int, input().split())
    c -= 1
    cards[c].append(p)

print(" ".join(map(lambda l : str(solve_card(l)), cards)))