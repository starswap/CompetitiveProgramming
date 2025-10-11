from math import floor
N = int(input())

maximum = 0
for i in range(N):
    sign = input()
    if sign == "/":
        print((floor(maximum / 10) + 1) * 10)
    else:
        score = int(sign)
        maximum = max(maximum, score)
        print(score)
