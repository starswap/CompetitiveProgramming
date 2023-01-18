T = int(input())
for t in range(T):
    w, d, h = map(int, input().split())
    lx, ly, px, py = map(int, input().split())

    print(
        min(
            px + h + lx + abs(ly - py),
            (w - px) + h + (w - lx) + abs(ly - py),
            py + h + ly + abs(lx - px),
            (d - py) + h + (d - ly) + abs(lx - px)
        )
    )