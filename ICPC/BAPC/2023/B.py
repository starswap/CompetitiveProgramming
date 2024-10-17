from fractions import Fraction
N = Fraction(int(input()))
i = 0
while N >= 2:
    i += 1
    N /= 2
while N > 0:
    i += 1
    N -= 1
print(i)
