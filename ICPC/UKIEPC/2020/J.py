import math
co, e, m = map(int, input().split())
EPS = 0.00000001
if co != 4 or e % 2 != 0:
    print("impossible")
else:
    a = 1
    b = (-4 - e // 2)
    c = (e + 4 + m)
    if (b * b - 4 * a * c) < 0:
        print("impossible")
    else:
        # print(b)
        # print(c)
        # print(b * b - 4 * a * c)
        # print(math.sqrt(b*b - 4 * a * c))
        disc = b*b - 4 * a * c
        if (math.isqrt(disc) * math.isqrt(disc)  != disc):
            print("impossible")
        else:
            h_1 = (-b + math.isqrt(disc)) / (2 * a)
            h_2 = (-b - math.isqrt(disc)) / (2 * a)
            w = max(h_1, h_2)
            h = min(h_1, h_2)
            # w = (e // 2) + 4 - h
            # print(w)
            # print(h)
            if abs(round(w) - w) > EPS or abs(round(h) - h) > EPS:
                print("impossible")
            else:
                print(f"{round(w)} {round(h)}") # round


# (w + h - 4) = e / 2
# (w * h - 2w - 2h + 4) = m

# w = (e / 2) + 4 - h
# (h * [(e/2) + 4 - h]) - 2h -2(e/2 + 4 -h) + 4 = m
# (e/2)*h + 4h - h^2  - e - 4  - m = 0

# h^2 + e + 4 + m - 4h - (e/2)h = 0
# (1) * h^2 + (-4 -e/2)*h + (e + 4 + m) = 0
